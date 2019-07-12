package videoeditor.videoeffect.opengl;

import android.view.Surface;

public class NativeOpengl {

    static {
        System.loadLibrary("native-lib");
    }

    public native void surfaceCreate(Surface surface);

    public native void surfaceChange(int width,int height);

    public native void imgData(int w, int h ,int lenth, byte[] data);

}
