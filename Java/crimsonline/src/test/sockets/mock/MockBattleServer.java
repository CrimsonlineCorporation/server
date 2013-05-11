package test.sockets.mock;

import com.google.gson.Gson;
import test.beans.BattleCreationRequest;
import test.beans.BattleServerRegistration;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;

import static test.sockets.BattleServersRecorder.LOCALHOST;
import static test.sockets.BattleServersRecorder.PORT_NUMBER;

/**
 * Stub to imitate battle server's connection
 * User: user
 * Date: 09.05.13
 * Time: 21:58
 */
public class MockBattleServer extends AbstractSocketMock {
    private final static int COUNT_BATTLES = 13;
    private BattleCreationRequest address;

    public static void main(String[] args) {
        MockBattleServer mockBattleServer = new MockBattleServer();
        mockBattleServer.mock(LOCALHOST, PORT_NUMBER);
        mockBattleServer.connectToTransmitter();
    }

    @Override
    protected void interact() throws IOException {
        System.out.println("Send request...");
        sendBattleServerRegistration(writer, COUNT_BATTLES);

        System.out.println("Read response...");
        address = readAddress(reader);
    }

    private void connectToTransmitter() {
        connectToAddress(address);
    }

    private void sendBattleServerRegistration(final PrintWriter writer, final int countOfBattles) throws IOException {
        BattleServerRegistration request = new BattleServerRegistration(countOfBattles);
        Gson gson = new Gson();
        String json = gson.toJson(request, BattleServerRegistration.class);
        System.out.println("  Request for registration: " + json);
        writer.println(json);
    }

    private BattleCreationRequest readAddress(final BufferedReader reader) throws IOException {
        Gson gson = new Gson();
        String json = reader.readLine();
        BattleCreationRequest response = gson.fromJson(json, BattleCreationRequest.class);
        if (response != null) {
            System.out.println("  Got address: " + response.getConnectAddress() + ":" + response.getConnectPort());
        } else {
            System.out.println("  Can't parse response!");
        }
        return response;
    }

    private void connectToAddress(final BattleCreationRequest address) {
        if (address == null) {
            System.out.println("  No address was passed!");
            return;
        }
        String host = address.getConnectAddress();
        int port = address.getConnectPort();

        MockBattleDataTransmitter mockBattleDataTransmitter = new MockBattleDataTransmitter();
        mockBattleDataTransmitter.mock(host, port);

    }

}
