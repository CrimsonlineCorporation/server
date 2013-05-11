package test.sockets.mock;

import java.io.*;
import java.net.Socket;

import static test.sockets.BattleServersRecorder.CHARSET_NAME;

/**
 * User: user
 * Date: 11.05.13
 * Time: 13:32
 */
public abstract class AbstractSocketMock {

    protected BufferedReader reader;
    protected PrintWriter writer;

    public void mock(String hostname, int port) {
        try {
            System.out.println("Connecting to " + hostname + ":" + port + "...");
            Socket clientSocket = new Socket(hostname, port);

            reader = createReader(clientSocket);
            writer = createWriter(clientSocket);

            System.out.println("Start data transmitting...");
            interact();
            System.out.println("Data transmission is finished.");

            System.out.println("Closing socket...");
            clientSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
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
