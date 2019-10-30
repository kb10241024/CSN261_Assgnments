import read.ReadTextAsString;
import trie.HashTrie;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.HashMap;

class q2 {
    static int counter = 0;

    static void print_scramble_words(HashMap<String, Integer> printed_words_map, HashTrie dictionary, int l,
            char word[], char newWord[], boolean taken[], int currentIndex) {
        if (currentIndex == l) {
            String scrambled = (new String(newWord)).toLowerCase();
            if (dictionary.contains(scrambled) && !printed_words_map.containsKey(scrambled)) {
                System.out.println(scrambled);
                printed_words_map.put(scrambled, 1);
                counter++;
            }
            return;
        }
        for (int i = 0; i < l; i++) {
            if (!taken[i]) {
                newWord[currentIndex] = word[i];
                taken[i] = true;
                print_scramble_words(printed_words_map, dictionary, l, word, newWord, taken, currentIndex + 1);

                taken[i] = false;
            }
        }
    }

    static void print_all_words(HashTrie dictionary, String str) {
        int length = str.length();
        for (int l = 4; l <= length; l++) {
            int c1 = counter;
            System.out.println("Words of length " + l + "  are : ");
            HashMap<String, Integer> printed_words_map = new HashMap<>();
            for (int i = 0; i + l <= length; i++) {
                char word[] = (str.substring(i, i + l)).toCharArray();
                char newWord[] = new char[l];
                boolean taken[] = new boolean[l];
                print_scramble_words(printed_words_map, dictionary, l, word, newWord, taken, 0);
            }
            System.out.println("Count : " + (counter - c1));
        }
    }

    static HashTrie create_dictionary(String filename) throws Exception {
        String words[] = ReadTextAsString.readFileAsString(filename);
        // for (int i = 0; i < words.length; i++) {
        // System.out.println(words[i]);
        // }
        HashTrie t = new HashTrie(words);
        return t;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Enter path to for the dictionary of words");
        String filename = br.readLine();
        HashTrie dictionary = create_dictionary(filename);

        char ch = 'n';
        do {
            System.out.println("\nEnter word to search ");
            String key = br.readLine();
            System.out.println("Search status : ");
            print_all_words(dictionary, key);

            System.out.println("\nDo you want to continue (Type y or n) \n");
            ch = br.readLine().charAt(0);
        } while (ch == 'Y' || ch == 'y');

    }
}