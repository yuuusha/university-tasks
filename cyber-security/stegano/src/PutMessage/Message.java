package PutMessage;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.SQLOutput;
import java.util.ArrayList;
import java.util.List;

public class Message {
    ArrayList<Byte> message;

    public Message(String path) {
        message = new ArrayList<>();

        if (path.equals("std")) {
            System.out.println("Message: ");
            try {
                byte[] bytes = System.in.readAllBytes();
                for (byte b : bytes) {
                    if (b != '\n')
                        message.add(b);
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        else {
            try (FileInputStream fis = new FileInputStream(path)) {
                byte[] buffer = new byte[1024];
                int bytesRead;
                while ((bytesRead = fis.read(buffer)) != -1) {
                    for (int i = 0; i < bytesRead; i++) {
                        message.add(i, buffer[i]);
                    }
                }
            } catch (IOException e) {
                throw new RuntimeException("Ошибка при чтении файла");
            }
        }
    }

    public void printMessage() {
        System.err.println("Message: ");
        for (byte b : message) {
            String binaryString = String.format("%8s", Integer.toBinaryString(b & 0xFF)).replace(' ', '0');
            System.err.println(binaryString);
        }
        System.err.println();
    }

    public String toString() {
        StringBuilder ret = new StringBuilder();
        for (byte b : message) {
            String binaryString = String.format("%8s", Integer.toBinaryString(b & 0xFF)).replace(' ', '0');
            ret.append(binaryString);
        }
        return ret.toString();
    }


}
