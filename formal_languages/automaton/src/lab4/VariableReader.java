package lab4;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class VariableReader {
    private final Map<String, Integer> variableMap = new HashMap<>();

    public void readFile(String filePath) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = reader.readLine()) != null) {
                line = line.trim();
                if (!line.isEmpty() && line.contains(":")) {
                    String[] parts = line.split(":");
                    if (parts.length == 2) {
                        String variableName = parts[0].trim();
                        try {
                            int variableValue = Integer.parseInt(parts[1].trim());
                            variableMap.put(variableName, variableValue);
                        } catch (NumberFormatException e) {
                            System.err.println("Некорректное значение переменной: " + parts[1].trim());
                        }
                    } else {
                        System.err.println("Некорректный формат строки: " + line);
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public Map<String, Integer> getVariableMap() {
        return variableMap;
    }

    public int getParam(String key) {
        if (!variableMap.containsKey(key)) {
            throw new RuntimeException("Переменная " + key + " не существует");
        }
        return variableMap.get(key);
    }
}
