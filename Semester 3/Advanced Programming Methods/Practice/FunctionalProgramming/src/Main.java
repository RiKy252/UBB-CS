import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) {

        // Filter to have only string that start with "c"
        // Upper case all the filtered elements
        // Sort them
        // Print each
        //
        // Output: C1
        //         C2
//        List<String> myList = Arrays.asList("a1", "a2", "b1", "c2", "c1");
//        myList.stream()
//                .filter(s -> s.startsWith("c"))
//                .map(String::toUpperCase)
//                .sorted()
//                .forEach(System.out::println);

        // Seminar 7
        // P1-P4
        List<String> words = Arrays.asList("hi", "hello", "salut", "ciao", "esti barosan", "aEr", "aer", "are", "bEe", "beEr");
//        words.stream()
//                .forEach(System.out::println);

        List<String> excitingWords = words.stream()
                                            .map(word -> word + "!")
                                            .collect(Collectors.toList());

        List<String> eyeWords = words.stream()
                .map(word -> word.replace("i", "eye"))
                .collect(Collectors.toList());

        List<String> upperCaseWords = words.stream()
                .map(word -> word.toUpperCase())
                .collect(Collectors.toList());

//        System.out.println("Exciting Words: " + excitingWords);
//        System.out.println("Eye Words: " + eyeWords);
//        System.out.println("Upper Case Words: " + upperCaseWords);

        List<String> shortWords = words.stream()
                .filter(word -> word.length() < 4)
                .collect(Collectors.toList());

        List<String> wordsWithB = words.stream()
                .filter(word -> word.contains("b"))
                .collect(Collectors.toList());

        List<String> evenLengthWords = words.stream()
                .filter(word -> (word.length() % 2) == 0)
                .collect(Collectors.toList());

//        System.out.println("Short Words: " + shortWords);
//        System.out.println("Words with b: " + wordsWithB);
//        System.out.println("Even length words: " + evenLengthWords);

        List<String> P5 = words.stream()
                .map(word -> word.toUpperCase())
                .filter(word -> word.length() < 4 && word.contains("E"))
                .collect(Collectors.toList());
//        System.out.println(P5);

        String P6 = words.stream()
                .reduce("", (acc, word) -> acc + word.toUpperCase());

//        System.out.println(P6);

        String P7 = words.stream()
                .map(word -> word.toUpperCase())
                .reduce("", (acc, word) -> acc + word);

//        System.out.println(P7);

        String P8 = words.stream()
                .reduce((acc, word) -> acc + "," + word)
                        .orElse("");

//        System.out.println(P8);

        int P9 = words.stream()
                .mapToInt(word -> word.length())
                .sum();

//        System.out.println(P9);

        long P10 = words.stream()
                .filter(word -> word.contains("h"))
                .count();

//        System.out.println(P10);

        // MAP theory 2023 v1

//        List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14,15);

        //a)eliminates all the numbers which neither are multiple of 3 nor of 4;
        //b)transform each remaining number into its succesor modulo 3;
        //c)compute the sum modulo 2 of the remaining numbers

//        int result = numbers.stream()
//                .filter(n -> n % 3 == 0 || n % 4 == 0)
//                .map(n -> (n + 1) % 3)
//                .reduce(0, Integer::sum) % 2;
//
//         System.out.println(result);

//        interface In1 { int getS1();}
//        class A implements In1 {
//            int f1;
//            static int s1=0;
//            public A(int a) { this.f1=a*s1;s1=s1+1; }
//            int getS() { return getS1(); }
//            int getS1() {return s1;}
//        }

        // MAP Theory 1 feb 2024

        List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
        int result = numbers.stream()
                .filter(n -> n % 3 == 0 || n % 7 == 0)
                .map(n -> (n - 1) * 10)
                .reduce(0, (acc, n) -> n + acc) % 5;
        System.out.println(result);

    }
}

abstract class A1 { abstract int getS1();}
class A extends A1 {
    static int f1;
    static int s1=0;
    public A(int a) { f1=a*s1;s1=s1+1; }
    static int getS() {
        A ob= new A(10);
        return ob.getS1();
    }
    int getS1() {return f1;}
}
// Static method -> cant reference a non-static method
//               -> same with the fields, can't contain non-static fields, because the static function does not have access
//                  to instance variables or methods, we can only fix this by creating an object and then extract values
//                  from the object instance

// Interface -> Methods implemented from an interface must be public.
// Abstract class -> default access modifier = package-private
//                   we don't need 'public' or other access modifier in the overridden method unless it reduces the visibility
//                   -> in this case we have package-private = package-private