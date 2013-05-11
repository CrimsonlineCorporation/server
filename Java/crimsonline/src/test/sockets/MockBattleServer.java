package test.sockets;

import com.google.gson.Gson;
import test.beans.BattleCreationRequest;
import test.beans.BattleServerRegistration;

import java.io.*;
import java.net.Socket;

import static test.sockets.BattleServersRecorder.*;

/**
 * Stub to imitate battle server's connection
 * User: user
 * Date: 09.05.13
 * Time: 21:58
 */
public class MockBattleServer {
    private final static int COUNT_BATTLES = 13;

    public static void main(String[] args) {
        try {
            Socket clientSocket = new Socket(LOCALHOST, PORT_NUMBER);

            BufferedReader reader = createReader(clientSocket);
            PrintWriter writer = createWriter(clientSocket);

            System.out.println("Send request...");
            sendBattleServerRegistration(writer, COUNT_BATTLES);

            System.out.println("Read response...");
            readAddress(reader);

            System.out.println("Closing socket...");
            clientSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static BufferedReader createReader(final Socket socket) throws IOException {
        InputStream in = socket.getInputStream();
        return new BufferedReader(new InputStreamReader(in, CHARSET_NAME));
    }

    private static PrintWriter createWriter(final Socket socket) throws IOException {
        OutputStream out = socket.getOutputStream();
        return new PrintWriter(new BufferedWriter(new OutputStreamWriter(out, CHARSET_NAME)), true);
    }

    private static void sendBattleServerRegistration(final PrintWriter writer, final int countOfBattles) throws IOException {
        BattleServerRegistration request = new BattleServerRegistration(countOfBattles);
        Gson gson = new Gson();
        String json = gson.toJson(request, BattleServerRegistration.class);
        writer.println(json);
    }

    private static void readAddress(final BufferedReader reader) throws IOException {
        Gson gson = new Gson();
        String json = reader.readLine();
        BattleCreationRequest response = gson.fromJson(json, BattleCreationRequest.class);
        if (response != null) {
            System.out.println("Got address: " + response.getConnectAddress() + ":" + response.getConnectPort());
        } else {
            System.out.println("Can't parse response!");
        }
    }
}
