/**
 * @author Traian Manolescu
 */

public class DynamicArray {

    // private fields
    private int[] array;
    private int size;

    /**
     * Dynamic Array constructor
     */
    public DynamicArray() {
        array = new int[3];
    }

    /**
     * 
     * @param capacity the full amount of potential space for the array
     * @throws IllegalArgumentException throws if the capacity is negative
     */
    public DynamicArray(int capacity) throws IllegalArgumentException {
        if (capacity < 0)
            throw new IllegalArgumentException();
        this.array = new int[capacity];
    }

    /**
     * Copy constructor that creates an identical Dynamic Array
     * @param obj new Dynamic Array
     * @throws IllegalArgumentException throws if the object is null
     */
    public DynamicArray(DynamicArray obj) throws IllegalArgumentException {
        if (obj == null)
            throw new IllegalArgumentException();
        //copies the other array onto the copy array
        array = obj.getArray();
        //sets the size to the original array's size
        size = obj.size;
    }

    /**
     * Returns the number of occupied spaces in the array
     * @return the amount of occupied spaces in the array
     */
    public int getSize() {
        return size;
    }

    /**
     * Returns the total amount of spaces (both empty and occupied)
     * @return Returns the capacity
     */
    public int getCapacity() {
        return array.length;
    }

    /**
     * Gets the number at a specific index in the array
     * @param i the user-inputted index
     * @return returns the number occupied at the index
     * @throws IndexOutOfBoundsException throws exception if the index provided is larger than the size of the array or less than 0
     */
    public int get(int i) throws IndexOutOfBoundsException {
        if (i < 0 || i >= size)
            throw new IndexOutOfBoundsException();
        return array[i];
    }

    /**
     * Tests if the array is empty
     * @return returns true if the array size is 0
     */
    public boolean isEmpty() {
        if (getSize() == 0)
            return true;
        return false;
    }

    /**
     * Returns the partially-filled array as a copy
     * @return returns the copied array
     */
    public int[] getArray() {
        int[] reArr = new int[getCapacity()];
        //for loop to add the values of the array into the copy
        for (int i = 0; i < array.length; i++) {
            reArr[i] = array[i];
        }
        return reArr;
    }

    /**
     * Returns an array of the occupied parts of the original array
     * @return returns the copied array
     */
    public int[] toArray() {
        int[] reArr = new int[size];
        //copies the contents of the array onto a new array based on the number of occupied spots of the original array
        for (int i = 0; i < size; i++) {
            reArr[i] = array[i];
        }
        return reArr;
    }

    /**
     * Returns the index of the first user-entered number in the array
     * @param num user-entered number in the array
     * @return returns the index of the number if found, returns -1 if not found
     */
    public int indexOf(int num) {
        //for loop for a linear search of the index of the user-given number
        for (int i = 0; i < size; i++) {
            //returns the index of the number if found
            if (array[i] == num)
                return i;
        }
        //returns -1 if not found
        return -1;
    }
    /**
     * Prints the occupied parts of the array into a string and returns the string
     */
    public String toString() {
        //returns "[ ]" if the size is zero
        if (size == 0)
            return "[ ]";
        //creates the beginning of the array
        String arrString = "[";
        //for loop to print the values of the array into the string
        for (int i = 0; i < size - 1; i++) {
            arrString += array[i] + ", ";
        }
        //adds a hard bracket to the end of the array along with the size of the last digit - 1
        arrString += array[size - 1] + "]";

        return arrString;
    }

    /**
     * Removes a digit at a given index in the array
     * @param index the index of the digit to be removed
     * @return returns the removed digit
     * @throws IndexOutOfBoundsException throws exception if the index is less than 0 or greater than the size of the array
     */
    public int remove(int index) throws IndexOutOfBoundsException {
        if (index >= size || index < 0)
            throw new IndexOutOfBoundsException();
        int toReturn = array[index];
        //if statement to cut capacity of the array in half
        if (getCapacity() >= getSize() * 4) {
            //new array to cut the capacity in half
            int[] newArr = new int[getCapacity() / 2];
            //for loop to add digits to the new array up to the index of the element to be removed
            for (int i = 0; i < index; i++) {
                newArr[i] = array[i];
            }
            //for loop to add digits to the new array after the index of the element to be removed
            for (int i = index; i < (size - 1); i++) {
                newArr[i] = array[i + 1];
            }
            //sets the current array to the new array
            array = newArr;
            //else statement for a normal array
        } else {
            //for loop to adjust the indexes of the numbers from the array
            for (int i = index; i < (size - 1); i++) {
                //sets all the elements' indexes forward to go over the index
                array[index] = array[index + 1];
            }
        }
        //decrements the size of the array
        size--;
        //returns the removed number
        return toReturn;
    }
    /**
     * 
     * @param index where in the array the integer will be added
     * @param num the new integer added to the array
     * @throws IndexOutOfBoundsException throws exception if the index is larger than the size of the array or less than 0
     */
    public void add(int index, int num) throws IndexOutOfBoundsException {
        if (index > size || index < 0)
            throw new IndexOutOfBoundsException();
        //doubles the size of the array if the array is full
        if (getCapacity() == getSize()) {
            //new array with double the capacity of the old array
            int[] newArr = new int[getCapacity() * 2];
            //adds the values up to the index being added to the new array
            for (int i = 0; i < index; i++) {
                newArr[i] = array[i];
            }
            //adds the new value to the index
            newArr[index] = num;
            //adds the rest of the original values after the index of the added value
            for (int i = index; i < size; i++) {
                newArr[i + 1] = array[i];
            }
            //sets the array as the new array
            array = newArr;
        } else {
            //moves all the numbers from the end of the array one over from the index of the added digit
            for (int i = size - 1; i >= index; i--) {
                array[i + 1] = array[i];
            }
            //adds the digit to the specified index
            array[index] = num;
        }
        //increments the size of the array
        size++;
    }

    /**
     * Removes the last digit of the array
     * @return returns the popped digit of the array
     * @throws RuntimeException throws when the array capacity is 0
     */
    public int pop() throws RuntimeException {
        if (getCapacity() == 0)
            throw new RuntimeException("The array is empty");
        //if statement if the capacity is over four times the array's size
        if (getCapacity() >= getSize() * 4) {
            //new array with capacity that is half the size
            int[] newArr = new int[getCapacity() / 2];
            //for loop to copy the values of the original array over
            for (int i = 0; i < size; i++) {
                newArr[i] = array[i];
            }
            //sets the array as the new array
            array = newArr;
        }
        //stores the popped digit
        int popDigit = array[size - 1];
        //decrements the size of the array
        size--;
        //returns the popped digit
        return popDigit;
    }

    /**
     * Adds a number to the end of the array
     * @param num
     */
    public void push(int num) {
        //if statement for if the size of the array is 0
        if (size == 0) {
            array[0] = num;
        }
        //creates a new array if the array is full
        if (getCapacity() == getSize()) {
            int[] newArr = new int[getCapacity() * 2];
            for (int i = 0; i < size; i++) {
                newArr[i] = array[i];
            }
            //sets the array as the new array
            array = newArr;
        }
        //sets the last digit of the array to the number to be added
        array[size] = num;
        //increments the size 
        size++;
    }

    /**
     * Compares two Dynamic Array objects
     * @param obj a fellow Dynamic Array object
     * @return returns true if the arrays are the same
     */
    public boolean equals(DynamicArray obj) {
        //returns false if the lengths are not equal
        if (obj.getSize() != size)
            return false;
        //for loop to check if the digits in the indexes are different
        for (int i = 0; i < size; i++) {
            //returns false if the digits are not equal to each other
            if (array[i] != obj.get(i))
                return false;
        }
        return true;
    }
}
