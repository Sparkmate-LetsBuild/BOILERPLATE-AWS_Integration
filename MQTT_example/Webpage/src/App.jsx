import { useEffect, useState } from "react";
// import Amplify from "aws-amplify";
// import { PubSub, Auth } from "aws-amplify";
// import { AWSIoTProvider } from "@aws-amplify/pubsub/lib/Providers";

import sparkIcon from "./assets/sparkIcon.png";
import "./App.css";

import {
  THING_NAMES,
  getRequestThingState,
  postRequestThingState,
} from "./AWS_functions";

function App() {
  const [things, setThings] = useState(THING_NAMES);

  /**
   * Uses getRequestThingState to retrieve the "actual" state of the button from AWS,
   * and set the React state to the things' states.
   */
  const getThingsState = async () => {
    const thingsState = await Promise.all(
      things.map(async (t) => {
        // Use getRequestThingState to retrieve the state, and map directly to the React object's state.
        return await getRequestThingState(t.id);
      })
    );
    setThings(
      things.map((t, index) => {
        return {
          ...t,
          state: thingsState[index]?.data?.status,
        };
      })
    );
  };

  /**
   * Uses postRequestThingState to set the desired state of the Thing via the AWS Shadow Function
   * @param {*} t
   * @returns
   */
  const toggleThingState = async (t) => {
    return await postRequestThingState(t.id, t.state);
  };

  useEffect(() => {
    setInterval(() => {
      getThingsState();
    }, 1000); // A "MDS polling" technique
  }, []);

  return (
    <div className="App">
      <div>
        <a href={"https://www.sparkmate.co/"}>
          <img src={sparkIcon} className="logo spark" alt="React logo" />
        </a>
      </div>
      <a href="https://github.com/Sparkmate-LetsBuild/">
        <h2 style={{ textAlign: "left" }}>Let's Build</h2>
      </a>
      <h1 style={{ textAlign: "center" }}>a MQTT-connected ESP32</h1>
      <h2 style={{ textAlign: "right" }}>with Sparkmate</h2>
      <p className="read-the-docs">
        Set and view the state of Things on AWS IoT Core.
      </p>
      <div className={"cards-container"}>
        {things.map((t) => {
          return (
            <div key={t.id} className="card">
              <p>
                {t.id} is {t.state ? "🌞" : "🌚"}
              </p>
              <button onClick={() => toggleThingState(t)}>Toggle lights</button>
            </div>
          );
        })}
      </div>
    </div>
  );
}

export default App;
