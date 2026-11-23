package repository.file;

import exception.RepositoryException;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

final class CsvSupport {
    private CsvSupport() { }

    /**
     * Ensures that the specified CSV file and its parent directories exist, creating them with the provided header if missing.
     *
     * @param path   the path to the CSV file
     * @param header the default header line to write if the file is created
     */
    static void ensureFile(Path path, String header) {
        try {
            Path parent = path.getParent();
            if (parent != null) Files.createDirectories(parent);
            if (!Files.exists(path)) {
                List<String> lines = new ArrayList<String>();
                lines.add(header);
                Files.write(path, lines, StandardCharsets.UTF_8);
            }
        } catch (IOException exception) {
            throw new RepositoryException("Nu pot pregati fisierul " + path + ".", exception);
        }
    }

    /**
     * Reads and returns all lines from the specified file using UTF-8 encoding.
     *
     * @param path the path to the file to read
     * @return a list of strings representing each line in the file
     */
    static List<String> readLines(Path path) {
        try {
            return Files.readAllLines(path, StandardCharsets.UTF_8);
        } catch (IOException exception) {
            throw new RepositoryException("Nu pot citi fisierul " + path + ".", exception);
        }
    }

    /**
     * Writes a list of text lines to the specified file using UTF-8 encoding.
     *
     * @param path  the path to the file to write to
     * @param lines the list of strings to write
     */
    static void writeLines(Path path, List<String> lines) {
        try {
            Files.write(path, lines, StandardCharsets.UTF_8);
        } catch (IOException exception) {
            throw new RepositoryException("Nu pot salva fisierul " + path + ".", exception);
        }
    }

    /**
     * Parses a single CSV row line into a list of field values, handling quotes and commas appropriately.
     *
     * @param line the raw CSV line string to parse
     * @return a list of extracted field values
     */
    static List<String> parseRow(String line) {
        List<String> fields = new ArrayList<String>();
        StringBuilder field = new StringBuilder();
        boolean quoted = false;
        for (int index = 0; index < line.length(); index++) {
            char character = line.charAt(index);
            if (character == '"') {
                if (quoted && index + 1 < line.length() && line.charAt(index + 1) == '"') {
                    field.append('"');
                    index++;
                } else {
                    quoted = !quoted;
                }
            } else if (character == ',' && !quoted) {
                fields.add(field.toString());
                field.setLength(0);
            } else {
                field.append(character);
            }
        }
        if (quoted) throw new RepositoryException("Linie CSV cu ghilimele incomplete: " + line);
        fields.add(field.toString());
        return fields;
    }

    /**
     * Formats and escapes a single field value for safe inclusion in a CSV format.
     *
     * @param value the raw string value to format
     * @return the escaped and properly quoted field string
     */
    static String formatField(String value) {
        String escaped = value.replace("\"", "\"\"");
        if (escaped.contains(",") || escaped.contains("\"") || escaped.contains("\n") || escaped.contains("\r")) {
            return "\"" + escaped + "\"";
        }
        return escaped;
    }
}