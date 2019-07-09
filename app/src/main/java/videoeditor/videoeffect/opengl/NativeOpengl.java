package videoeditor.videoeffect.opengl;

import android.view.Surface;

public class NativeOpengl {

    static {
        System.loadLibrary("native-lib");
    }

    public native void surfaceCreate(Surface surface);

}
