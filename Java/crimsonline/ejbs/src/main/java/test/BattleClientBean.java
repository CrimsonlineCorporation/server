package test;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.annotation.PreDestroy;
import javax.annotation.Resource;
import javax.ejb.Singleton;
import javax.ejb.Timeout;
import javax.ejb.TimerConfig;
import javax.ejb.TimerService;
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
    private static final long TIMEOUT_TO_TRANSMITTER_START = 1000;
    private ServerSocket serverSocket;
    private Socket clientSocket;
    private final Logger logger = LoggerFactory.getLogger(BattleClientBean.class);
    @Resource
    private TimerService timerService;

    public BattleClientBean() throws IOException {
        serverSocket = new ServerSocket(0);
    }

    public int getPort() {
        return serverSocket == null ? -1 : serverSocket.getLocalPort();
    }

    public void startListen() throws IOException {
        TimerConfig timerConfig = new TimerConfig();
        timerConfig.setPersistent(false);
        timerService.createSingleActionTimer(TIMEOUT_TO_TRANSMITTER_START, timerConfig);
    }

    @Timeout
    protected void listen() {
        logger.info("Transmitter is ready to connect...");
        try {
            while (!serverSocket.isClosed()) {
                logger.debug("Start listening for battle data...");
                clientSocket = serverSocket.accept();
                logger.debug("Connection with battle server is established.");
                serverSocket.close();
                logger.debug("Stop listening for battle data.");
            }
        } catch (IOException e) {
            logger.error("An error occurred during work of battle-server listener.", e);
        }
    }

    @PreDestroy
    public void stopClient() {
        try {
            if (serverSocket != null && !serverSocket.isClosed()) {
                logger.info("Transmitter's socket will be closed.");
                serverSocket.close();
            }
        } catch (Exception e) {
            logger.error("An error occurred during stopping of battle-server listener.", e);
        }
    }
}
