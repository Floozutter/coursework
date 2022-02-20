package dchoi933_CSCI201_Assignment1;

public class Main {
    private static final java.util.Scanner scan = new java.util.Scanner(System.in);
    private static final com.google.gson.Gson gson = (new com.google.gson.GsonBuilder())
        .setPrettyPrinting()
        .create();

    private static class SourcedCuff {
        public final java.nio.file.Path source;
        public final WristCuff cuff;
        SourcedCuff(java.nio.file.Path source, WristCuff cuff) {
            this.source = source;
            this.cuff = cuff;
        }
        public static SourcedCuff prompt() {
            while (true) {
                System.out.print("Please provide timefall shelter data source: ");
                final String pathstring = scan.nextLine();
                final java.nio.file.Path source;
                try {
                    source = java.nio.file.Paths.get(pathstring);
                } catch (java.nio.file.InvalidPathException e) {
                    System.out.printf("The string %s is not a valid path.%n%n", pathstring);
                    continue;
                }
                final String json;
                try {
                    json = java.nio.file.Files.readString(source);
                } catch (java.nio.file.NoSuchFileException e) {
                    System.out.printf("The file %s could not be found.%n%n", source);
                    continue;
                } catch (java.io.IOException | OutOfMemoryError | SecurityException e) {
                    System.out.printf("The file %s could not be read.%n%n", source);
                    continue;
                }
                final WristCuff cuff;
                try {
                    java.util.ArrayList<TimefallShelter> shelters = gson.fromJson(
                        json,
                        new com.google.gson.reflect.TypeToken<
                            java.util.ArrayList<TimefallShelter>
                        >(){}.getType()
                    );
                    cuff = new WristCuff(shelters);
                } catch (com.google.gson.JsonSyntaxException e) {
                    System.out.printf("The file %s could not be parsed.%n%n", source);
                    continue;
                }
                System.out.println("=== Data accepted ===");
                return new SourcedCuff(source, cuff);
            }
        }
    }

    private static class SupportedChiralFrequencies {
        public final java.util.Set<Integer> fs;
        SupportedChiralFrequencies(java.util.Set<Integer> fs) {
            this.fs = fs;
        }
        public static SupportedChiralFrequencies prompt() {
            while (true) {
                System.out.print("Please provide supported Chiral frequencies: ");
                final String line = scan.nextLine().replaceAll("\\s", "");
                if (line.chars().allMatch(c -> c == 44 || (48 <= c && c <= 57))) {
                    final java.util.Set<Integer> fs = java.util.Arrays.stream(line.split(","))
                        .filter(s -> !s.isBlank())
                        .mapToInt(Integer::parseInt)
                        .boxed().collect(java.util.stream.Collectors.toSet());
                    return new SupportedChiralFrequencies(fs);
                } else {
                    System.out.printf(
                        "The line could not be parsed as chiral frequencies (%s).%n%n",
                        "(Please enter a comma-separated list of integers.)"
                    );
                    continue;
                }
            }
        }
    }

    private static enum Option {
        INVALID, LIST, SEARCH_BY_FREQUENCY, SEARCH_BY_NAME, SORT, JUMP;
        public static Option prompt() {
            final String[] lines = {
                "1) List all available shelters matching the supported Chiral frequencies",
                "2) Search for a shelter by Chiral frequency",
                "3) Search for a shelter by name",
                "4) Sort shelters by Chiral frequency",
                "5) Jump to a shelter with the lowest supported Chiral frequency",
            };
            for (String line : lines) {
                System.out.println(line);
            }
            System.out.print("Choose an option: ");
            switch (scan.nextLine().strip()) {
            default : return INVALID;
            case "1": return LIST;
            case "2": return SEARCH_BY_FREQUENCY;
            case "3": return SEARCH_BY_NAME;
            case "4": return SORT;
            case "5": return JUMP;
            }
        }
    }

    private static void listAction(WristCuff cuff, SupportedChiralFrequencies supported) {
        final java.util.List<TimefallShelter> shelters = cuff.shelters.stream()
            .filter(ts -> supported.fs.contains(ts.chiralFrequency))
            .collect(java.util.stream.Collectors.toList());
        System.out.printf("%d results%n%n", shelters.size());
        for (TimefallShelter ts : shelters) {
            System.out.println(ts);
        }
    }

    private static void searchByFrequencyAction(WristCuff cuff) {
        System.out.print("What is the shelter's Chiral frequency? ");
        final String s = scan.nextLine();
        System.out.println();
        int fTemporary;  // i hate java
        try {
            fTemporary = Integer.parseInt(s);
        } catch (NumberFormatException e) {
            fTemporary = -1;
        }
        final int f = fTemporary;
        final java.util.Optional<TimefallShelter> res = cuff.shelters.stream()
            .filter(ts -> ts.chiralFrequency == f)
            .findAny();
        if (res.isPresent()) {
            System.out.printf("Found!%n%n%s%n", res.get());
        } else {
            System.out.println("No such shelter...\n");
        }
    }

    private static void searchByNameAction(WristCuff cuff) {
        System.out.print("What is the shelter's name? ");
        final String name = scan.nextLine();
        System.out.println();
        final java.util.Optional<TimefallShelter> res = cuff.shelters.stream()
            .filter(ts -> ts.name.equalsIgnoreCase(name))
            .findAny();
        if (res.isPresent()) {
            System.out.printf("Found!%n%n%s%n", res.get());
        } else {
            System.out.println("No such shelter...\n");
        }
    }

    private static void sortAction(SourcedCuff sc) {
        java.util.Collections.sort(sc.cuff.shelters);
        final String json = gson.toJson(sc.cuff.shelters);
        try {
            java.nio.file.Files.writeString(sc.source, json);
            System.out.println("Shelters successfully sorted by Chiral frequency.\n");
        } catch (java.io.IOException | OutOfMemoryError | SecurityException e) {
            System.out.println("Could not write to timefall shelter data source.\n");
        }
    }

    private static void jumpAction(SourcedCuff sc, SupportedChiralFrequencies supported) {
        System.out.println("=== Commencing timefall shelter search ===");
        final java.util.List<TimefallShelter> shelters = sc.cuff.shelters.stream()
            .filter(ts -> supported.fs.contains(ts.chiralFrequency))
            .collect(java.util.stream.Collectors.toList());
        java.util.Collections.sort(shelters);
        boolean doomed = true;
        for (TimefallShelter ts : shelters) {
            if (ts.timefall) {
                System.out.printf(
                    "Chiral frequency %d unstable, Chiral jump unavailable. ===%n",
                    ts.chiralFrequency
                );
                System.out.print("=== Removing target shelter from the list of shelters and ");
                System.out.print(" saving updated list to disk. ===\n");
                sc.cuff.shelters.remove(ts);
            } else {
                System.out.println("=== Matching timefall shelter found! ===");
                System.out.println(ts);
                doomed = false;
                break;
            }
        }
        final String json = gson.toJson(sc.cuff.shelters);
        try {
            java.nio.file.Files.writeString(sc.source, json);
        } catch (java.io.IOException | OutOfMemoryError | SecurityException e) {
            System.out.println("Could not write to timefall shelter data source.\n");
        }
        if (doomed) {
            System.out.println("=== No shelter available. You are DOOMED. ===");
        } else {
            System.out.println("=== Commencing Chiral jump, see you in safety. ===");
        }
    }

    public static void main(String[] args) {
        System.out.println("Welcome to Bridges Link.");
        System.out.println();
        final SourcedCuff sc = SourcedCuff.prompt();
        System.out.println();
        final SupportedChiralFrequencies supported = SupportedChiralFrequencies.prompt();
        System.out.println();
        loop: while (true) {
            final Option o = Option.prompt();
            System.out.println();
            switch (o) {
            case INVALID            : System.out.println();
            case LIST               : listAction(sc.cuff, supported); break;
            case SEARCH_BY_FREQUENCY: searchByFrequencyAction(sc.cuff); break;
            case SEARCH_BY_NAME     : searchByNameAction(sc.cuff); break;
            case SORT               : sortAction(sc); break;
            case JUMP               : jumpAction(sc, supported); break loop;
            }
        }
    }
}
