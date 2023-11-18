import org.opencv.core.Core;

public class Main {
    static{ System.loadLibrary(Core.NATIVE_LIBRARY_NAME); }
    public static void main(String[] args) {
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
        MainFrame mainFrame = new MainFrame();
        mainFrame.setSize(1400, 800);
        mainFrame.setVisible(true);

        System.out.println(Math.sqrt(-9.0));
        

    }
    public static class MyInner
    {
        public static void foo() { }
    }
}