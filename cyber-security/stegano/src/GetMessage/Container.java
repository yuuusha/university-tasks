package GetMessage;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;

public class Container {
    private final String filePath;

    public Container(String filePath) {
        this.filePath = filePath;
    }

    public void process(String messagePath) {
        ArrayList<Character> chars = new ArrayList<>();

        if (filePath.equals("std")) {
            System.out.println("Container: ");
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
                String line;

                while ((line = reader.readLine()) != null && !line.isEmpty()) {
                    if (checkIfEnd(line)) {
                        break;
                    }
                    chars.add(getByteFromLine(line));
                }

            } catch (IOException e) {
                throw new RuntimeException("Ошибка при обработке ввода", e);
            }
        }
        else {
            try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
                String line;

                while ((line = reader.readLine()) != null) {
                    if (checkIfEnd(line)) {
                        break;
                    }
                    chars.add(getByteFromLine(line));
                }

            } catch (IOException e) {
                throw new RuntimeException("Ошибка при обработке файла", e);
            }
        }

        ArrayList<Byte> byteList = new ArrayList<>();
        StringBuilder currentByte = new StringBuilder();

        for (Character c : chars) {
            currentByte.append(c);
            if (currentByte.length() == 8) {
                int value = Integer.parseInt(currentByte.toString(), 2);
                byteList.add((byte) value);
                currentByte.setLength(0);
            }
        }

        Message message = new Message(byteList);

        if (messagePath.equals("std")) {
            message.printMessage();
        }
        else {
            try {
                Files.write(Paths.get(messagePath), message.string());
            } catch (IOException e) {
                throw new RuntimeException("Ошибка при обработке файла");
            }
        }

    }

    private char getByteFromLine(String line) {
        if (line.endsWith(" ")) {
            return '0';
        }
        return '1';
    }

    private boolean checkIfEnd(String line) {
        return line.endsWith("  ");
    }
}
