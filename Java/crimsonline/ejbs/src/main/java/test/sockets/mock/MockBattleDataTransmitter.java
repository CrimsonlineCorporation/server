package test.sockets.mock;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.IOException;

/**
 * User: user
 * Date: 11.05.13
 * Time: 14:55
 */
public class MockBattleDataTransmitter extends AbstractSocketMock {
    private final Logger logger = LoggerFactory.getLogger(MockBattleDataTransmitter.class);
    @Override
    protected void interact() throws IOException {
        logger.debug("Client stub...");
    }
}
