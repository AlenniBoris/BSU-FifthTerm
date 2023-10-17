package ColorModels;

import Frames.MainFrame;

import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import java.awt.*;

public class HSL_Model extends JPanel {
    private JTextField enterH;
    private JTextField enterS;
    private JTextField enterL;

    private MainFrame frame;

    public HSL_Model(MainFrame mainFrame) {
        this.enterH = new JTextField("0");
        this.enterS = new JTextField("0");
        this.enterL = new JTextField("0");
        this.frame = mainFrame;

        setLayout(new GridLayout(4,0));
        add(new JLabel("HSL(°,%,%)"));
        add(enterH);
        addListener(enterH);
        add(enterS);
        addListener(enterS);
        add(enterL);
        addListener(enterL);

    }



    public int getH() {
        return Integer.parseInt(enterH.getText());
    }
    public double getS() {
        return Double.parseDouble(enterS.getText());
    }
    public double getL() {
        return Double.parseDouble(enterL.getText());
    }

    private void addListener(JTextField textField){
        textField.getDocument().addDocumentListener(new DocumentListener() {
            @Override
            public void insertUpdate(DocumentEvent e) {
                if (textField.hasFocus()){
                    makeChanges(textField);
                }
            }

            @Override
            public void removeUpdate(DocumentEvent e) {
                if (textField.hasFocus()){
                    makeChanges(textField);
                }
            }

            @Override
            public void changedUpdate(DocumentEvent e) {
                if (textField.hasFocus()){
                    makeChanges(textField);
                }
            }
        });
    }

    public JTextField getEnterH() {
        return enterH;
    }

    public JTextField getEnterS() {
        return enterS;
    }

    public JTextField getEnterL() {
        return enterL;
    }

    public void makeChanges(JTextField textField){
        if (!textField.getText().isEmpty()){
            try{
                double value = Double.parseDouble(textField.getText());
                if (value >= 0){
                    if (textField == enterH && value < 360){
                        double S = Double.parseDouble(enterS.getText())*Math.pow(10,-2);
                        double L = Double.parseDouble(enterL.getText())*Math.pow(10,-2);
                        changeRGB((int) value,S,L);
                        frame.getSliderPanel().getHslSlider().gethSlider().setValue((int) value);
                    } else if (textField == enterS && value <= 100) {
                        int H = Integer.parseInt(enterH.getText());
                        double L = Double.parseDouble(enterL.getText())*Math.pow(10,-2);
                        changeRGB(H, value*Math.pow(10,-2),L);
                        frame.getSliderPanel().getHslSlider().getsSlider().setValue((int) (value));
                    } else if (textField == enterL && value <= 100){
                        int H = Integer.parseInt(enterH.getText());
                        double S = Double.parseDouble(enterS.getText())/100;
                        changeRGB(H,S,value*Math.pow(10,-2));
                        frame.getSliderPanel().getHslSlider().getlSlider().setValue((int) (value));
                    }
                }else {
                    JOptionPane.showMessageDialog(frame,"Enter number in 0..255");
                }
            }catch (NumberFormatException e){
                JOptionPane.showMessageDialog(frame,"Enter only digits");
            }
        }
    }
    public void changeTextFields(int H, double S, double L){
        enterH.setText(Integer.toString(H));
        enterS.setText(Double.toString(Math.round(S)));
        enterL.setText(Double.toString(Math.round(L)));

        frame.getSliderPanel().getHslSlider().gethSlider().setValue(H);
        frame.getSliderPanel().getHslSlider().getsSlider().setValue((int) S);
        frame.getSliderPanel().getHslSlider().getlSlider().setValue((int) L);
    }

    private void changeRGB(int H, double S, double L){
        double C = (1-Math.abs(2*L-1))*S;
        double X = C*(1-Math.abs((H/60)%2-1));
        double m = L- C/2;

        double r = 0;
        double g = 0;
        double b = 0;

        if (0 <= H && H < 60){
            r = C;
            g = X;
            b = 0;
        } else if (60 <= H && H < 120){
            r = X;
            g = C;
            b = 0;
        } else if (120 <= H && H < 180) {
            r = 0;
            g = C;
            b = X;
        } else if (180 <= H && H < 240) {
            r = 0;
            g = X;
            b = C;
        } else if (240 <= H && H < 300) {
            r = X;
            g = 0;
            b = C;
        } else if (300 <= H && H < 360) {
            r = C;
            g = 0;
            b = X;
        }

        frame.getRGB().changeTextFields((int) (255*(r+m)), (int) (255*(g+m)), (int) (255*(b+m)));
        frame.getRGB().changeCMYK(frame.getRGB().getR(), frame.getRGB().getG(), frame.getRGB().getB());
        frame.getColorPanel().setBackground(new Color((int) (255*(r+m)), (int) (255*(g+m)), (int) (255*(b+m))));
    }
}