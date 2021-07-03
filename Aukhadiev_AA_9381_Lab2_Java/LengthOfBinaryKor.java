import java.util.Scanner;
import java.io.*;

class Cargo{
    private boolean tag; //=false, если груз - гирька, =true, если груз - коромысло
    private int m; //масса гирьки (=0, если коромысло)
    private BinKor bk; //бинарное коромысло (=null, если груз - гирька)

    public Cargo(StringBuilder str){
        if(str.charAt(0) == '('){
            tag = true;
            bk = new BinKor(str);
        }else if(Character.isDigit(str.charAt(0))){
            tag = false;
            String numbers = str.toString().split("(?=\\D)")[0];
            m = Integer.parseInt(numbers);
            str.delete(0, (int)Math.log10(m) + 1);
        }else{
            System.out.println("ERROR");
            System.exit(0);
        }
        if(str.isEmpty())
            return;
        while(str.charAt(0) == ' ' || str.charAt(0) == ')'){
            str.delete(0,1);
            if(str.isEmpty())
                break;
        }
    }

    public int length(int tab){
        int len = 0;
        if(tag)
            len += bk.length();
        return len;
    }
}

class Shoulder{
    private int len; //длина плеча
    private Cargo cargo; //груз

    public Shoulder(StringBuilder str){
        if(Character.isDigit(str.charAt(0))) {
            String numbers = str.toString().split("(?=\\D)")[0];
            len = Integer.parseInt(numbers);
            str = str.delete(0, (int) Math.log10(len) + 1);
        }else{
            System.out.println("ERROR");
            System.exit(0);
        }
        while(str.charAt(0) == ' ')
            str.delete(0, 1);
        cargo = new Cargo(str);
    }

    public int lengthShoulder(int tab, int num){
        for(int i = 0; i < tab; i++)
            System.out.print("\t");
        System.out.println("Поиск длины плеча № " + tab + "." + num);
        int length = cargo.length(tab) + len;
        for(int i = 0; i < tab; i++)
            System.out.print("\t");
        System.out.println("Длина плеча № " + tab + "." + num + " = " + length);
        return length;

    }
}

class BinKor{
    private Shoulder pl1; //левое плечо
    private Shoulder pl2; //правое плечо

    public BinKor(StringBuilder str){
        if(str.charAt(0) == '(' && str.charAt(1) == '('){
            str = str.delete(0, 2);
            pl1 = new Shoulder(str);
        }else{
            System.out.println("ERROR");
            System.exit(0);
        }

        if(str.charAt(0) == '(' && str.charAt(1) != '('){
            str = str.delete(0, 1);
            pl2 = new Shoulder(str);
        }else{
            System.out.println("ERROR");
            System.exit(0);
        }
    }

    public int length(){
        int tab = LengthOfBinaryKor.globalTab++;
        for(int i = 0; i < tab; i++){
            System.out.print("\t");
        }
        tab++;
        System.out.println("Нахождение длины коромысла № " + tab);
        int len = pl1.lengthShoulder(tab, 1);
        len += pl2.lengthShoulder(tab, 2);
        for(int i = 0; i < tab; i++)
            System.out.print("\t");
        System.out.println("Длина коромысла № " + tab + " = " + len);
        return len;
    }
}

public class LengthOfBinaryKor {
    public static int globalTab = 0;

    public static void main(String[] args) throws IOException {

        int choise = 1;
        Scanner inChoise = new Scanner(System.in);
        Scanner inString = new Scanner(System.in);
        String str = new String();

        System.out.println("Выберите формат ввода: 0 - из файла, 1 - консоль");
        choise = inChoise.nextInt();
        if(choise == 0){
            System.out.println("Введите название файла");
            String fileName = inString.nextLine();
            File file = new File(fileName);
            if(!file.exists()){
                System.out.println("Файл не найден");
                return;
            }
            FileReader fileReader = new FileReader(file);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            str = bufferedReader.readLine();
        }else if(choise == 1){
            System.out.println("Введите строку: ");
            str = inString.nextLine();
        }else{
            System.out.println("ERROR");
            return;
        }
        StringBuilder string = new StringBuilder(str);
        BinKor binKor = new BinKor(string);
        int length = binKor.length();
        System.out.println(length);
    }
}
