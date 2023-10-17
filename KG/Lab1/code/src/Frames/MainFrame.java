package Frames;

import javax.swing.*;
import java.awt.*;
import ColorModels.*;
import Sliders.*;

public class MainFrame extends JFrame {

    private JPanel leftPanel;
    private JPanel rightPanel;
    private JPanel colorPanel;
    private RGB_Model RGB;
    private CMYK_Model CMYK;
    private HSL_Model HSL;

    private SliderPanel sliderPanel;

    private ChooseFromPalitra chooseFromPalitra;
    public MainFrame() throws HeadlessException {
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        setLayout(new GridLayout(0, 2));

        leftPanel = new JPanel(new GridLayout(2, 0));

        colorPanel = new JPanel();
        colorPanel.setBackground(Color.black);
        leftPanel.add(colorPanel);

        JPanel enters = new JPanel(new GridLayout(0, 3));
        leftPanel.add(enters);
        RGB = new RGB_Model(this);
        enters.add(RGB);
        CMYK = new CMYK_Model(this);
        enters.add(CMYK);
        HSL = new HSL_Model(this);
        enters.add(HSL);

        rightPanel = new JPanel(new GridLayout(2, 0));

        chooseFromPalitra = new ChooseFromPalitra(this);
        rightPanel.add(chooseFromPalitra);
        sliderPanel = new SliderPanel(this);
        rightPanel.add(sliderPanel);


        add(leftPanel);
        add(rightPanel);
    }

    public HSL_Model getHSL() {
        return HSL;
    }

    public RGB_Model getRGB() {
        return RGB;
    }

    public CMYK_Model getCMYK() {
        return CMYK;
    }

    public JPanel getColorPanel() {
        return colorPanel;
    }

    public SliderPanel getSliderPanel() {
        return sliderPanel;
    }
}