package com.lazyee.demo.rsa

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.lazyee.demo.rsa.databinding.ActivityMainBinding
import com.lazyee.module.rsa.RSAUtil

class MainActivity : AppCompatActivity() {
    private val mViewBinding by lazy { ActivityMainBinding.inflate(layoutInflater) }
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(mViewBinding.root)

        mViewBinding.tvEncrypt.text = RSAUtil.encryptByRSAPublicKey("hello,lazyee")
        mViewBinding.tvDecrypt.text = RSAUtil.decryptByRSAPrivateKey(mViewBinding.tvEncrypt.text.toString())
    }
}