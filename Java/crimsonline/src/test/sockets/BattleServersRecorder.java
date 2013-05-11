package test.sockets;

import com.google.gson.Gson;
import test.BattleClientBean;
import test.beans.BattleCreationRequest;
import test.beans.BattleServerRegistration;

import javax.annotation.PreDestroy;
import javax.annotation.Resource;
import javax.ejb.*;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * User: user
 * Date: 03.05.13
 * Time: 18:16
 */
@Singleton
public class BattleServersRecorder implements IBattleServersRecorder {
    public static final int PORT_NUMBER = 40000;
    public static final String CHARSET_NAME = "UTF-8";
    public static final String LOCALHOST = "localhost";
    public static final long TIMEOUT_TO_BATTLE_SERVER_RECORDER_START = 1000;
    @EJB
    BattleClientBean battleClient;
    @Resource
    private TimerService timerService;

    public BattleServersRecorder() {
    }

    public void initRecorder() {
        TimerConfig timerConfig = new TimerConfig();
        timerConfig.setPersistent(false);
        timerService.createSingleActionTimer(TIMEOUT_TO_BATTLE_SERVER_RECORDER_START, timerConfig);
    }

    @Timeout
    public void listen() {
        System.out.println("Recorder is started.");
        try (ServerSocket serverSocket = new ServerSocket(PORT_NUMBER)) {
            while (!serverSocket.isClosed()) {
                System.out.println("Socket is still opened...");
                Socket clientSocket = serverSocket.accept();
                System.out.println("Accepted connection from client...");

                BufferedReader reader = createReader(clientSocket);
                PrintWriter writer = createWriter(clientSocket);

                int battleCount = getCountBattles(reader);
                System.out.println("Received '" + battleCount + "' count of battles");

                if (battleCount > 0) {
                    int connectPort = battleClient.getPort();
                    System.out.println("Port is '" + connectPort + "'");
                    battleClient.startListen();

                    BattleCreationRequest request = new BattleCreationRequest(LOCALHOST, connectPort);
                    sendBattleAddress(request, writer);
                    writer.flush();
                }

                System.out.println("Stop data transmission.");
                serverSocket.close();

            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private int getCountBattles(final BufferedReader reader) throws IOException {
        Gson parser = new Gson();
        String json = reader.readLine();
        BattleServerRegistration registration = parser.fromJson(json, BattleServerRegistration.class);
        return registration == null ? -1 : registration.getCountBattles();
    }

    private void sendBattleAddress(final BattleCreationRequest request, final PrintWriter writer) {
        Gson parser = new Gson();
        String json = parser.toJson(request, BattleCreationRequest.class);
        writer.println(json);
    }

    private BufferedReader createReader(final Socket socket) throws IOException {
        InputStream in = socket.getInputStream();
        return new BufferedReader(new InputStreamReader(in, CHARSET_NAME));
    }

    private PrintWriter createWriter(final Socket socket) throws IOException {
        OutputStream out = socket.getOutputStream();
        return new PrintWriter(new BufferedWriter(new OutputStreamWriter(out, CHARSET_NAME)));
    }

    @PreDestroy
    protected void finishTransmitter() {
        System.out.println("Recorder is finished.");
    }
}