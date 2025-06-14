package PutMessage;

import java.io.*;

public class Container {
    private final String filePath;

    public Container(String filePath) {
        this.filePath = filePath;
    }

    public void process(Message message, String outputFilePath) {
        char[] chars = message.toString().toCharArray();
        StringBuilder res = new StringBuilder();

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {

            String line;

            for (char bit : chars) {
                if ((line = reader.readLine()) != null) {
                    line = line.stripTrailing();
                    line = modifyLineWithByte(line, bit);

                    if (!res.isEmpty()) {
                        res.append("\n");
                    }
                    res.append(line);
                }
            }

            if ((line = reader.readLine()) != null) {
                if (!res.isEmpty()) {
                    res.append("\n");
                }
                res.append(line).append("  ");
            }
            else {
                throw new RuntimeException("Недостаточно строк в контейнере");
            }

            while ((line = reader.readLine()) != null) {
                res.append("\n").append(line);
            }

        } catch (IOException e) {
            throw new RuntimeException("Ошибка при обработке файла", e);
        }

        if (outputFilePath.equals("std")) {
            System.out.println("Стегоконтейнер: ");
            System.out.println(res);
        } else {
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFilePath))) {
                writer.write(res.toString());
            } catch (IOException e) {
                throw new RuntimeException("Ошибка при обработке файла");
            }
        }
    }

    private String modifyLineWithByte(String line, char bit) {
        StringBuilder modifiedLine = new StringBuilder(line);

        if (bit == '0') {
            modifiedLine.append(" ");
        }

        return modifiedLine.toString();
    }
}
