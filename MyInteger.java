/**
 * @author Traian Manolescu
 */

public class MyInteger {
    private int userInt;

    /**
     * Constructor method
     * @param userInt creates the integer userInt
     */
    public MyInteger(int userInt) {
        this.userInt = userInt;
    }

    /**
     * Checks if the number is prime
     * @return true if the number is prime, false if not
     */
    public boolean isPrime() {
        if (userInt <= 1)
            return false;
        else {
            for (int i = 2; i <= userInt / 2; i++) {
                if (userInt % i == 0)
                    return false;
            }
        }
        return true;
    }

    /**
     * Checks if the integer is even
     * @return true if the remainder is 0
     */
    public boolean isEven() {
        if (userInt % 2 == 0) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Checks if the integer is odd
     * @return true if the remainder is 1
     */
    public boolean isOdd() {
        if (userInt % 2 == 1) {
            return true;
        } else {
            return false;
        }
    }
/**
 * returns the value of userInt
 * @return userInt
 */
    public int toInteger() {
        return userInt;
    }

    /**
     * Checks if a specified value is even
     * @param num the integer being compared
     * @return true if the integer is even
     */
    public static boolean isEven(int num) {
        if (num % 2 == 0) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Checks if a specified value is odd
     * @param num the integer being compared
     * @return true if the integer is odd
     */
    public static boolean isOdd(int num) {
        if (num % 2 == 1) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Checks if a specified value is prime
     * @param num the integer being compared
     * @return true if the integer is prime
     */
    public static boolean isPrime(int num) {
        if (num <= 1)
            return false;
        else {
            for (int i = 2; i <= num / 2; i++) {
                if (num % i == 0)
                    return false;
                break;
            }
        }
        return true;
    }

    /**
     * turns a string into an integer- throws exceptions when:
     * there is stack overflow and underflow
     * there is only a '-'
     * there are any non-digit numbers
     * @param s the integer stored into a string
     * @return
     */
    public static int parseInt(String s) {
        boolean negative = false;
        long maxValue = Integer.MAX_VALUE;
        long minValue = Integer.MIN_VALUE;
        long myNum = 0;
        // checks if the string is only a '-' sign
        if (s.length() == 1 && s.charAt(0) == '-')
            throw new IllegalArgumentException();
        // determines if the string is a negative or positive number
        if (s.charAt(0) == '-') {
            negative = true;
        }
        // writes the string into a long
        if (negative == true) {
            for (int i = 1; i < s.length(); i++) {
                myNum += ((s.charAt(i) - 48) * Math.pow(10, (s.length() - i)) / -10);
            }
        } else {
            for (int i = 0; i < s.length(); i++) {
                myNum += ((s.charAt(i) - 48) * Math.pow(10, (s.length() - i)) / 10);
            }
        }
        // throws exception if any non-digit characters are in the string (additional
        // loop for positive number)
        if (negative = true)
            for (int i = 1; i < s.length(); i++) {
                if (!(s.charAt(i) >= '0' && s.charAt(i) <= '9')) {
                    throw new IllegalArgumentException();
                }
            }
        if (negative = false)
            for (int i = 0; i < s.length(); i++) {
                if (!(s.charAt(i) >= '0' && s.charAt(i) <= '9')) {
                    throw new IllegalArgumentException();
                }
            }
        // checks if the number is too large or small to be an integer
        if (myNum > maxValue || myNum < minValue) {
            throw new IllegalArgumentException();
        }
        return (int) myNum;
    }

    public boolean equals(MyInteger obj) {
        return this.userInt == obj.userInt;
    }

    public boolean equals(int c) {
        return this.userInt == c;
    }

    // setter and getter
    public int getInt() {
        return userInt;
    }

    public void setInt(int myInt) {
        userInt = myInt;
    }
}
