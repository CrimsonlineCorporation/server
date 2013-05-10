package test;

import javax.annotation.PreDestroy;
import javax.ejb.Singleton;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * User: user
 * Date: 04.05.13
 * Time: 17:25
 */
@Singleton
public class BattleClientBean {
    private ServerSocket serverSocket;
    private Socket clientSocket;

    public BattleClientBean() throws IOException {
        serverSocket = new ServerSocket(0);
    }

    public int getPort() {
        return serverSocket.getLocalPort();
    }

    public void startListen() throws IOException {
        while (serverSocket.isClosed()) {
            clientSocket = serverSocket.accept();
        }
    }

    @PreDestroy
    public void stopClient() {
        try {
            if (serverSocket != null && !serverSocket.isClosed()) {
                serverSocket.close();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
