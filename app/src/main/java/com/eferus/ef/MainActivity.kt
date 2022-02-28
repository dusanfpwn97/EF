package com.eferus.ef

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.eferus.ef.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI2()
    }

    /**
     * A native method that is implemented by the 'ef' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI2(): String

    companion object {
        // Used to load the 'ef' library on application startup.
        init {
            System.loadLibrary("ef")
        }
    }
}