package BackendPractice;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.charset.StandardCharsets;

public class UDPEchoClient {

    private static String str;
    private static BufferedReader buf;

    private static int SERVERPORT = 3000;

    public static void UDPEchoClient(String ip, int port) {
        try {
            InetAddress ia = InetAddress.getByName(ip);
            DatagramSocket socket = new DatagramSocket(port);
            System.out.println("message :");

            buf = new BufferedReader(new InputStreamReader(System.in));
            str = buf.readLine();
            byte buffer[] = str.getBytes(StandardCharsets.UTF_8);
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length, ia, SERVERPORT);
            socket.send(packet);
            buffer = new byte[512];
            packet = new DatagramPacket(buffer, buffer.length);
            socket.receive(packet);
            System.out.println("server IP : " + packet.getAddress());
            System.out.println("수신된 데이터: " + new String(packet.getData()).trim());
        } catch(IOException ioe){
            ioe.printStackTrace();
        }
    }

    public static void main(String[] args) {

        UDPEchoClient("localhost",2000);
    }

}
