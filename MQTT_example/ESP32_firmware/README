# ESP32 Firmware MQTT example to AWS

## Code flow

- This is a standard Arduino/micro-controller code flow, with a `setup` and a `loop`.
- The `setup` begins core systems and the UX (button and light), connects to your WiFi, and finally connects to the AWS endpoints (using the secrets you define).
- The `loop` polls the MQTT endpoint periodically (every 200ms, but this can be changed), and reports if the value of the button has changed. If the value has changed, `publishMessage` reports the change in the desired state to AWS, who in turn changes the _"shadow update delta"_ which emits a message on this topic that we listen to. Any changes on the  _"shadow update delta"_ topic that we see will change the state locally of the LED (i.e. turn it on or off).

**using interrupts with `publishMessage` (and why we don't)**

- Just note that interrupt routines are designed to be extremely short lasting.
- However the `publishMessage` (which has `Serial.print`, `client.publish`, and `serializeJson` within it) is a relatively long function to run (on the order of a few milliseconds).
- There is likely a better way to publish the messages than I have done here, maybe you can improve this for me in a Pull Request.. 😉

## Security (Secrets)

- You will need to generate secrets in order to securely connect to the AWS endpoint. See the [parent's folder's readme](../README) to understand how to generate these secrets.
- Secrets are set in the [secrets](./include/configs/secrets.h) file.
