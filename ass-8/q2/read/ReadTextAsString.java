package read;

import java.io.*;

import java.nio.file.*;;

public class ReadTextAsString {
    public static String[] readFileAsString(String fileName) throws Exception {
        String data = "";
        data = new String(Files.readAllBytes(Paths.get(fileName)));
        String words[] = data.split("\n");
        return words;
    }

    // public static void main(String[] args) throws Exception {
    // String words[] = readFileAsString("dummy_dict.txt");
    // System.out.println(words.length);
    // for (int i = 0; i < words.length; i++) {
    // System.out.println(words[i]);
    // }
    // System.out.println("endOfFile");

    // }
}