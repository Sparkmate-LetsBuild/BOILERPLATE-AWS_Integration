# Webplatform to AWS Shadow function

- All the AWS IoT Core functionality can be found in [./src/AWS_functions.js](./src/AWS_functions.js)
- All the webpage code can be found in [./src/App.jsx](./src/App.jsx)

## Shadow Endpoints

- Set your endpoint settings in the [./src/AWS_functions.js](./src/AWS_functions.js) file.

```jsx
const AWS_REGION = "eu-west-3"; // double check your region is correct
const API_URL = "[YOUR ENDPOINT NAME]";
const SHADOW_GET_ENDPOINT = "Shadow_Status_Check";
const SHADOW_POST_ENDPOINT = "Shadow_Update"; // this is what we've called it, you can call this endpoint something else
```

- This hooks to a Lambda function in IoT Core that we've called `Shadow_Update`

```py
import json
import boto3
import logging

logger = logging.getLogger()
logger.setLevel(logging.INFO)

client = boto3.client('iot-data')

def lambda_handler(event, context):
    print(json.dumps(event['body']))

    body = event['body']
    body = json.loads(body)

    THINGNAME=body['thingname']
    if (THINGNAME == ""):
        print("No Thing Name found. Setting Thing Name = ESP2")
        THINGNAME="ESP32"

    if body['action'] == "on":
        payload = json.dumps({'state': { 'desired': { 'status': True } }})

        logger.info("Attempting to Update Shadow State to ON")
        response = client.update_thing_shadow(
            thingName=THINGNAME,
            payload=payload
        )
        logger.info("IOT Shadow Updated")
    else:
        payload = json.dumps({'state': { 'desired': { 'status': False } }})

        logger.info("Attempting to Update Shadow State to OFF")
        response = client.update_thing_shadow(
            thingName=THINGNAME,
            payload=payload
        )
        logger.info("IOT Shadow Updated")


    return {
        'statusCode': 200,
        "headers": {
            'Access-Control-Allow-Origin':'*',
            'Access-Control-Allow-Headers':'Content-Type,X-Amz-Date,Authorization,X-Api-Key,X-Amz-Security-Token',
            'Access-Control-Allow-Methods':'GET,OPTIONS'
        },
    }
```

## Running

- Ensure you have [node.js](https://nodejs.org/en/download/) and [yarn](https://classic.yarnpkg.com/lang/en/docs/install/#windows-stable) installed
- then run `yarn run dev` to run the server.
