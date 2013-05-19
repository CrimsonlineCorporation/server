package test.sockets;

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
    @EJB
    private IBattleServersRecorder battleServersRecorder;

    @PostConstruct
    public void initialize() {
        System.out.println("Socket's initializer is started.");
        battleServersRecorder.initRecorder();

        System.out.println("Socket's initializer finished initialization.");
    }
}
