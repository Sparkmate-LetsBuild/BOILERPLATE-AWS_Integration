<a href="https://docs.platformio.org/en/latest/platforms/espressif32.html">
    <image src="https://img.shields.io/badge/🤖%20ESP32%20Arduino--green" />
</a>
<a href="https://reactjs.org/">
    <image src="https://img.shields.io/badge/🌐%20Web%20Platform--green" />
</a>
<a href="https://console.aws.amazon.com/console">
    <image src="https://img.shields.io/badge/🧠%20AWS%20IoTCore--green" />
</a>

<hr><br>

# MQTT | ESP32 ↔ Webplatform via AWS shadow functions

Use this example to have MQTT communication between a device and AWS IoT Core, as well as an included webplatform to see and set the state of the device.

**Device to AWS back to device operation**

- The device has a button that sends a `DESIRED` state message to AWS IoT Core.
- If the device button's state is now different to the recorded state on IoT Core, AWS issues a `delta` message with the required change for the light on the `update/delta` topic.
- The device constantly listens on this topic, setting the light's status to whatever is published on the `update/delta` topic.

**Webplatform to device operation**

- When the on/off buttons are pressed on the webplatform, the `DESIRED` state of the device changes on the AWS IoT Core, which in turn emit a new `delta` message.
- The device is still listening on this `delta` topic, so sees the change and changes the light to on/off.

**Device to webplatform operation**

- When the `delta` messages are emitted from AWS to the device, the webplatform is also subscribed to this topic so is able to see the changes.
- These changes are reflected by the emojis in the webplatform.

## Tutorial

To create this boilerplate we combined:

- https://aws.amazon.com/blogs/compute/building-an-aws-iot-core-device-using-aws-serverless-and-an-esp32/
- https://catalog.us-east-1.prod.workshops.aws/workshops/5b127b2f-f879-48b9-9dd0-35aff98c7bbc/en-US

You should be able to follow along with these tutorials, and the boilerplate here. If you get stuck, feel free to get in touch at [letsbuild@sparkmate.co](mailto:letsbuild@sparkmate.co), or be a real hero and open an issue in [the Github repo](https://github.com/Sparkmate-LetsBuild/BOILERPLATE-AWS_Integration) 💪.

## Secrets and Security

We found the above tutorial a little non-intuitive on the secrets/security part, so here's how we did it:

<image src="./readme_assets/creating_thing_security_1.PNG" width="500"/>
<image src="./readme_assets/creating_thing_security_2.PNG" width="500"/>
<image src="./readme_assets/creating_thing_security_3.PNG" width="500"/>
<image src="./readme_assets/creating_thing_security_4.PNG" width="500"/>
