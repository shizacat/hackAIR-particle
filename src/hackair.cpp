/* hackair library by Alexey M
 */

#include "hackair.h"

Hackair::Hackair(char* t)
{
    token = t;

    // default
    host = HOST_DEFAULT;
    path = PATH_DEFAULT;
}

/**
 * Send measurements to server
 */
uint8_t Hackair::send_data(float pm25, float pm10)
{
    unsigned char buff[1024];
    int len, ret;
    String message;

    tls_client.init(ca_cert, sizeof(ca_cert));

    if (tls_client.connect((char*) host.c_str(), port) < 0) {
        tls_client.stop();
        return -2;
    }

    if (!tls_client.verify()) {
      // "Server Certificates is in-valid."
      // return -1;
    }

    message = "{\"reading\": {\"PM2.5_AirPollutantValue\":\"" +
        String::format("%.1f", pm25) + "\",\"PM10_AirPollutantValue\":\"" +
        String::format("%.1f", pm10)+"\"}}";

    len = 0;
    // --- Header
    ret = sprintf((char *) &buff[len], "POST %s HTTP/1.1\r\n", path.c_str());
    len = len + ret;
    ret = sprintf((char *) &buff[len], "Host: %s\r\n", host.c_str());
    len = len + ret;
    ret = sprintf((char *) &buff[len], "Content-Length: %d\r\n", message.length());
    len = len + ret;
    ret = sprintf((char *) &buff[len], "Content-Type: application/json\r\n");
    len = len + ret;
    ret = sprintf((char *) &buff[len], "Accept: application/vnd.hackair.v1+json\r\n");
    len = len + ret;
    ret = sprintf((char *) &buff[len], "Authorization: %s\r\n", token.c_str());
    len = len + ret;
    // --- End Header
    ret = sprintf((char *) &buff[len], "\r\n");
    len = len + ret;
    // --- Body
    ret = sprintf((char *) &buff[len],"%s", message.c_str());
    len = len + ret;

    tls_client.write(buff, len);

    // GET HTTPS response.
    // memset(buff, 0, sizeof(buff));
    // while(1) {
    //     // read renponse.
    //     memset(buff, 0, sizeof(buff));
    //     int ret = tls_client.read(buff, sizeof(buff) - 1);
    //     if (ret == MBEDTLS_ERR_SSL_WANT_READ) {
    //         delay(100);
    //         continue;
    //     } else if (ret <= 0) {
    //         // no more read.
    //         break;
    //     } else if (ret > 0){
    //         Serial.println((char *)buff);
    //     }
    // }

    tls_client.stop();

    return 0;
}
