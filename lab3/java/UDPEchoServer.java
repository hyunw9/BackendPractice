package BackendPractice;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class UDPEchoServer {

    public static void UDPEchoServer(int port){
        try{
            DatagramSocket socket = new DatagramSocket(port);
            while(true){
                byte buffer[] = new byte[512];
                DatagramPacket packet = new DatagramPacket(buffer,buffer.length);
                System.out.println("Receiving . . .");
                socket.receive(packet);
                String str = new String(packet.getData());
                System.out.println("수신된 데이터: " + str);

                InetAddress ia = packet.getAddress();
                port = packet.getPort();
                System.out.println("Client IP : "+ ia + ", Client port :  "+ port);
                packet = new DatagramPacket(packet.getData(), packet.getLength(),ia,port);
                socket.send(packet);
            }
        } catch (IOException ioe){
            ioe.printStackTrace();
        }
    }

    public static void main(String[] args) {
        UDPEchoServer(3000);
    }

}
