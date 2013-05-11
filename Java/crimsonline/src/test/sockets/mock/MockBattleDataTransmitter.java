package test.sockets.mock;

import java.io.IOException;

/**
 * User: user
 * Date: 11.05.13
 * Time: 14:55
 */
public class MockBattleDataTransmitter extends AbstractSocketMock {
    @Override
    protected void interact() throws IOException {
        System.out.println("Client stub...");
    }
}
