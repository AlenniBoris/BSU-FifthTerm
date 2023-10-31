import org.opencv.core.*;
import org.opencv.imgproc.Imgproc;

public class ElementTransformations {
    static Mat addValue(Mat image, int value) {
        Mat processed = new Mat(image.size(), image.type());
        if (value >= 0) {
            Core.add(image, new Scalar(Math.abs(value), Math.abs(value), Math.abs(value)), processed);
        } else {
            Core.subtract(image, new Scalar(Math.abs(value), Math.abs(value), Math.abs(value)), processed);
        }
        return processed;
    }

    static Mat toNegative(Mat image) {
        Mat processed = new Mat(image.size(), image.type());
        Core.bitwise_not(image, processed);
        return processed;
    }

    static Mat multiplyValue(Mat image, double value) {
        Mat processed = new Mat(image.size(), image.type());
        if (value <= 0) {
            throw new IllegalArgumentException("Not so low value");
        }
        Core.multiply(image, new Scalar(value, value, value), processed);
        return processed;
    }

    static Mat powerValue(Mat image, double value) {
        Mat processed = new Mat(image.size(), image.type());
        image.copyTo(processed);
        processed.convertTo(processed, CvType.CV_32F);
        Core.pow(processed, value, processed);
        processed.convertTo(processed, image.type());
        return processed;
    }

    static Mat logarithm(Mat image) {
        Mat processed = new Mat(image.size(), image.type());
        image.copyTo(processed);
        Core.normalize(processed, processed, 0, 1, Core.NORM_MINMAX, CvType.CV_32F);
        Core.log(processed, processed);
        Core.normalize(processed, processed, 0, 255, Core.NORM_MINMAX, CvType.CV_8U);
        return processed;
    }

    static Mat linearContrast(Mat image, int min, int max) {
        Mat processed = new Mat(image.size(), image.type());
        for (int i = 0; i < image.rows(); i++) {
            for (int j = 0; j < image.cols(); j++) {
                double[] pixel = image.get(i, j);
                double[] post = new double[3];
                for (int k = 0; k < pixel.length; k++) {
                    post[k] = (double) ((double) (255 / (max - min)) * (pixel[k] - min));
                }
                processed.put(i, j, post);
            }
        }
        return processed;
    }

    static Mat Bernsen(Mat image, int size, int C) {
        Mat processed = new Mat(image.size(), image.type());
        Mat gray = new Mat(image.size(), image.type());
        Imgproc.cvtColor(image, gray, Imgproc.COLOR_BGR2GRAY);
        Imgproc.adaptiveThreshold(gray, processed, 255, Imgproc.ADAPTIVE_THRESH_MEAN_C, Imgproc.THRESH_BINARY, size, C);
        return processed;
    }

    static Mat Niblack(Mat image, int n, double k) {
        Mat processed = new Mat();
        image.copyTo(processed);
        int w = (n - 1) / 2;
        for (int i = w; i < image.rows() - w; i++) {
            for (int j = w; j < image.cols() - w; j++) {
                Rect roi = new Rect(j - w, i - w, n, n);
                Mat block = new Mat(image, roi);

                Scalar mean = Core.mean(block);
                MatOfDouble std = new MatOfDouble();
                Core.meanStdDev(block, new MatOfDouble(), std);
                double wBmn = mean.val[0];
                double wBstd = std.get(0, 0)[0];

                double wBTH = wBmn + k * wBstd;

                double pixelValue = image.get(i, j)[0];
                if (pixelValue < wBTH) {
                    processed.put(i, j, 0, 0, 0);
                } else {
                    processed.put(i, j, 255, 255, 255);
                }
            }
        }
        return processed;
    }
}
