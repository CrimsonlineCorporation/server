package test.sockets;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.annotation.PostConstruct;
import javax.ejb.EJB;
import javax.ejb.Singleton;
import javax.ejb.Startup;

/**
 * User: user
 * Date: 10.05.13
 * Time: 15:44
 */
@Startup
@Singleton
public class BattleServerSocketInitializerBean {
    private final Logger logger = LoggerFactory.getLogger(BattleServerSocketInitializerBean.class);

    @EJB
    private IBattleServersRecorder battleServersRecorder;

    @PostConstruct
    public void initialize() {
        logger.info("Socket's initializer is started.");
        battleServersRecorder.initRecorder();

        logger.info("Socket's initializer finished initialization.");
    }
}
