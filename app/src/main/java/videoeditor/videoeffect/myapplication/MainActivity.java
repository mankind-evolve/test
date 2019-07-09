package videoeditor.videoeffect.myapplication;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.SurfaceView;
import android.widget.TextView;

import videoeditor.videoeffect.opengl.NativeOpengl;
import videoeditor.videoeffect.opengl.WLSurfaceView;

public class MainActivity extends AppCompatActivity {

    private WLSurfaceView surfaceview;
    private NativeOpengl nativeOpengl;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        surfaceview = findViewById(R.id.surfaceview);
        nativeOpengl = new NativeOpengl();
        surfaceview.setNativeOpengl(nativeOpengl);
    }


}
