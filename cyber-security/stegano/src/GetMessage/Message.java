package GetMessage;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;

public class Message {
    ArrayList<Byte> message;

    public Message(ArrayList<Byte> message) {
        this.message = new ArrayList<>(message);
    }

    public void printMessage() {
        System.out.println("Message: ");
        for (byte b : message) {
            String binaryString = String.format("%8s", Integer.toBinaryString(b & 0xFF)).replace(' ', '0');
            System.out.println(binaryString);
        }
        System.out.println();
    }

    public byte[] string() {
        byte[] byteArray = new byte[message.size()];

        for (int i = 0; i < message.size(); i++) {
            byteArray[i] = message.get(i);
        }

        return byteArray;
    }
}
