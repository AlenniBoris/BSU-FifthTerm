package Sliders;

import Frames.MainFrame;
import Sliders.CMYK_Slider;
import Sliders.HSL_Slider;
import Sliders.RGB_Slider;

import javax.swing.*;
import java.awt.*;

public class SliderPanel extends JPanel {
    private JPanel btnPanel;
    private JTabbedPane tabbedPane;
    private RGB_Slider rgbSlider;
    private CMYK_Slider cmykSlider;
    private HSL_Slider hslSlider;
    private MainFrame frame;

    public SliderPanel(MainFrame mainFrame) {
        setLayout(new BorderLayout());

        frame = mainFrame;

        tabbedPane = new JTabbedPane();
        rgbSlider = new RGB_Slider(frame);
        cmykSlider = new CMYK_Slider(frame);
        hslSlider = new HSL_Slider(frame);
        tabbedPane.addTab("RGB", rgbSlider);
        tabbedPane.addTab("CMYK", cmykSlider);
        tabbedPane.addTab("HSL", hslSlider);

        add(new JLabel("Choose slider"), BorderLayout.NORTH);
        add(tabbedPane);
    }

    public RGB_Slider getRgbSlider() {
        return rgbSlider;
    }

    public CMYK_Slider getCmykSlider() {
        return cmykSlider;
    }

    public HSL_Slider getHslSlider() {
        return hslSlider;
    }
}
