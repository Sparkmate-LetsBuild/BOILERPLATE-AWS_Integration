const AWS_REGION = "eu-west-3";
const API_URL = "https://1a54q7i4bh.execute-api.eu-west-3.amazonaws.com/DEV";
const SHADOW_GET_ENDPOINT = "Shadow_Status_Check";
const SHADOW_POST_ENDPOINT = "Shadow_Update";

import axios from "axios";

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

/**
 * Declare the Things that we will use.
 * TODO this could be a function that loops through all Things on IoT Core and we generate this list dynamically.
 */
export const THING_NAMES = [
  {
    id: "matts_esp32",
  },
  {
    id: "matts_other_esp32",
  },
];

/**
 * Retrieve the state of a given Thing from AWS IoT Core
 */
export const getRequestThingState = (thingname) => {
  return axios.get(`${API_URL}/${SHADOW_GET_ENDPOINT}?thingname=${thingname}`);
};

/**
 * Set the state of a given Thing in AWS IoT Core (using the Shadow Functions)
 * @param {String} thingname
 * @param {Boolean} state
 */
export const postRequestThingState = (thingname, state) => {
  axios.post(
    `${API_URL}/${SHADOW_POST_ENDPOINT}`,
    JSON.stringify({
      thingname: thingname,
      action: state ? "off" : "on",
    }),
    {
      headers: {
        "Content-Type": "application/json",
      },
    }
  );
};
