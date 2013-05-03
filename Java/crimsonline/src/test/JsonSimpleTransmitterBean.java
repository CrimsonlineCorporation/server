package test;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;
import javax.ejb.Singleton;
import javax.ejb.Startup;
import javax.ejb.Stateless;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Created with IntelliJ IDEA.
 * User: user
 * Date: 03.05.13
 * Time: 18:16
 */
@Stateless
@Startup
@Singleton(name = "JsonSimpleTransmitterEJB")
public class JsonSimpleTransmitterBean {
    public static final int PORT_NUMBER = 40000;
    public static final int READ_BUFFER_SIZE = 65536; // 64*1024
    public static final String CHARSET_NAME = "UTF-8";

    private ServerSocket serverSocket;

    public JsonSimpleTransmitterBean() {
    }

    @PostConstruct
    protected void initTransmitter() {
        System.out.println("Transmitter is ready.");
        try {
            serverSocket = new ServerSocket(PORT_NUMBER);
            while (!serverSocket.isClosed()) {
                Socket clientSocket = serverSocket.accept();
                System.out.println("Accepted connection from client...");

                InputStream in = clientSocket.getInputStream();
                OutputStream out = clientSocket.getOutputStream();

                int battleCount = getCountBattles(in);
                System.out.println("Received '" + battleCount + "' count of battles");

            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private int getCountBattles(InputStream in) throws IOException {
        String clientMessage = read(in);
        if (clientMessage == null || "null".equals(clientMessage) || clientMessage.isEmpty()) {
            return -1;
        }

        JSONParser parser = new JSONParser();
        try {
            Object uncasted = parser.parse(clientMessage);
            if (uncasted instanceof JSONObject) {
                JSONObject message = (JSONObject) uncasted;
                System.out.println("Message is '" + message.toString() + "'");
                return ((Long) message.get("countBattles")).intValue();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -2;
    }

    protected String read(final InputStream input) throws IOException {
        byte[] buffer = new byte[READ_BUFFER_SIZE];
        int length = input.read(buffer);
        if (length <= 0) {
            return null;
        }
        String result = new String(buffer, 0, length, CHARSET_NAME);
        return result;
    }

    protected void write(final OutputStream out, final String text) throws IOException {
        if (text != null && out != null) {
            out.write(text.getBytes(CHARSET_NAME));
        }
    }

    protected void write(final OutputStream out, final Object object) throws IOException {
        if (object != null && out != null) {
            write(out, object.toString());
        }
    }

    @PreDestroy
    protected void finishTransmitter() {
        System.out.println("Transmitter is finished.");
    }
}
