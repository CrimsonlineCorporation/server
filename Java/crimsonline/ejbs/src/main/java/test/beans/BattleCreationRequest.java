package test.beans;

/**
 * User: user
 * Date: 04.05.13
 * Time: 16:18
 */
public class BattleCreationRequest {
    private int connectPort;
    private String connectAddress;

    public BattleCreationRequest(String connectAddress, int connectPort) {
        this.connectAddress = connectAddress;
        this.connectPort = connectPort;
    }

    public void setConnectPort(int connectPort) {
        this.connectPort = connectPort;
    }

    public void setConnectAddress(String connectAddress) {
        this.connectAddress = connectAddress;
    }

    public String getConnectAddress() {
        return connectAddress;
    }

    public int getConnectPort() {
        return connectPort;
    }
}
