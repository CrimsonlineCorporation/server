package test.sockets;

import javax.ejb.Remote;

/**
 * User: user
 * Date: 10.05.13
 * Time: 15:53
 */
@Remote
public interface IBattleServersRecorder {
    public void listen();

    public void initRecorder();
}
