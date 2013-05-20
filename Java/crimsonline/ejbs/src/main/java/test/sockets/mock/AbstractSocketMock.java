package test.sockets.mock;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.*;
import java.net.Socket;

import static test.sockets.BattleServersRecorder.CHARSET_NAME;

/**
 * User: user
 * Date: 11.05.13
 * Time: 13:32
 */
public abstract class AbstractSocketMock {
    private final Logger logger = LoggerFactory.getLogger(AbstractSocketMock.class);
    protected BufferedReader reader;
    protected PrintWriter writer;

    public void mock(String hostname, int port) {
        try {
            logger.debug("Connecting to {}:{}...", hostname, port);
            Socket clientSocket = new Socket(hostname, port);

            reader = createReader(clientSocket);
            writer = createWriter(clientSocket);

            logger.debug("Start data transmitting...");
            interact();
            logger.debug("Data transmission is finished.");

            logger.debug("Closing socket...");
            clientSocket.close();
        } catch (IOException e) {
            logger.error("An error occurred during mocking of socket!", e);
        }
    }

    protected BufferedReader createReader(final Socket socket) throws IOException {
        InputStream in = socket.getInputStream();
        return new BufferedReader(new InputStreamReader(in, CHARSET_NAME));
    }

    protected PrintWriter createWriter(final Socket socket) throws IOException {
        OutputStream out = socket.getOutputStream();
        return new PrintWriter(new BufferedWriter(new OutputStreamWriter(out, CHARSET_NAME)), true);
    }

    protected abstract void interact() throws IOException;

}
