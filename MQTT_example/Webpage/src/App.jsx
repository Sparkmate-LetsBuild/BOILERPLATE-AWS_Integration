import { useEffect, useState } from "react";
import axios from "axios";
// import Amplify from "aws-amplify";
// import { PubSub, Auth } from "aws-amplify";
// import { AWSIoTProvider } from "@aws-amplify/pubsub/lib/Providers";

import sparkIcon from "./assets/sparkIcon.png";
import "./App.css";

const AWS_REGION = "eu-west-3";
const API_URL = "https://1a54q7i4bh.execute-api.eu-west-3.amazonaws.com/DEV";
const SHADOW_GET_ENDPOINT = "Shadow_Status_Check";
const SHADOW_POST_ENDPOINT = "Shadow_Update";
// Amplify.configure({
//   Auth: {
//     identityPoolId: process.env.REACT_APP_IDENTITY_POOL_ID,
//     region: AWS_REGION,
//     userPoolId: process.env.REACT_APP_USER_POOL_ID,
//     userPoolWebClientId: process.env.REACT_APP_USER_POOL_WEB_CLIENT_ID,
//   },
// });

// // Apply plugin with configuration
// Amplify.addPluggable(
//   new AWSIoTProvider({
//     aws_pubsub_region: AWS_REGION,
//     aws_pubsub_endpoint:
//       "wss://a1n8k13y0lb4kl-ats.iot.eu-west-3.amazonaws.com/mqtt",
//   })
// );

// Amplify.PubSub.subscribe("esp32/states").subscribe({
//   next: (data) => console.log("Message received", data),
//   error: (error) => console.error(error),
//   close: () => console.log("Done"),
// });

function App() {
  const [things, setThings] = useState([
    {
      id: "matts_esp32",
    },
    {
      id: "matts_other_esp32",
    },
  ]);

  const getThingsState = async () => {
    const thingsState = await Promise.all(
      things.map(async (t) => {
        return await axios.get(
          `${API_URL}/${SHADOW_GET_ENDPOINT}?thingname=${t.id}`
        );
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

  const toggleThingState = async (t) => {
    return await axios.post(
      `${API_URL}/${SHADOW_POST_ENDPOINT}`,
      JSON.stringify({
        thingname: t.id,
        action: t.state ? "off" : "on",
      }),
      {
        headers: {
          "Content-Type": "application/json",
        },
      }
    );
  };

  useEffect(() => {
    // getThingsState();
    setInterval(() => {
      getThingsState();
    }, 1000);
  }, []);

  return (
    <div className="App">
      <div>
        <img src={sparkIcon} className="logo spark" alt="React logo" />
      </div>
      <h1>Sparky</h1>
      <p className="read-the-docs">Let's play with Matt's things</p>
      <div className={"cards-container"}>
        {things.map((t) => {
          return (
            <div key={t.id} className="card">
              <p>
                {t.id} is {t.state ? "🌞" : "🌚"}
              </p>
              <button onClick={() => toggleThingState(t)}>Toggle light</button>
            </div>
          );
        })}
      </div>
    </div>
  );
}

export default App;
