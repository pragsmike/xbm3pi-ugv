#include "mbed.h"
#include "XBeeApi.h"


XBeeApi::XBeeApi(PinName p_tx, PinName p_rx, PinName p_rst): _xbee(p_tx, p_rx), _rst(p_rst) {
    _xbee.begin(19200);
    _rst = 0;
    wait_ms(1);
    _rst = 1;
    wait_ms(1);
    unread = 0;
}

int XBeeApi::readable() {
    if (unread > 0)
        return 1;
    _xbee.readPacket();
    if (_xbee.getResponse().isAvailable() && (_xbee.getResponse().getApiId() == RX_16_RESPONSE)) {
        _xbee.getResponse().getRx16Response(response);
        unread = response.getDataLength();
        return unread > 0;
    }
    return 0;
}

int XBeeApi::getc() {
    if (unread > 0) {
        return response.getData()[response.getDataLength()-unread--];
    }
    return -1;
}

void XBeeApi::send(uint8_t *payload, int payloadLength) {
     Tx16Request req(0x1234, DISABLE_ACK_OPTION, payload, payloadLength, 0);
    _xbee.send(req);
}