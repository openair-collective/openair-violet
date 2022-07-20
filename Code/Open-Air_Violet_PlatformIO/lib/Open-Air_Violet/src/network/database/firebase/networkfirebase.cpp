#include "networkfirebase.hpp"

// Define Firebase Data object
FirebaseData fbdata;

FirebaseAuth auth;
FirebaseConfig config;

NetworkFirebase::NetworkFirebase() : _auth_ok(false), _sendDataPreviousMillis(0), _sendDataInterval(0) {}

NetworkFirebase::~NetworkFirebase() {}

bool NetworkFirebase::begin_firebase()
{
    config.api_key = FIREBASE_API_KEY;

    /* Assign the RTDB URL (required) */
    config.database_url = FIREBASE_DATABASE_URL;

    /* Sign up */
    if (!Firebase.signUp(&config, &auth, "", ""))
    {
        log_e("%s\n", config.signer.signupError.message.c_str());
    }

    log_i("[Firebase] Sign up success");
    _auth_ok = true;

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}

/**
 * @brief Process the Firebase data. This function is called by the main loop.
 *
 * Possible functions: set, setInt, setFloat, setDouble, setString, setJSON, setArray, setBlob, and setFile
 */
void NetworkFirebase::process_firebase()
{
    if (Firebase.ready() && _auth_ok && (millis() - _sendDataPreviousMillis > 15000 || _sendDataPreviousMillis == 0))
    {
        _sendDataPreviousMillis = millis();
        // Write an Int number on the database path test/int
        if (Firebase.RTDB.setInt(&fbdata, "test/int", _sendDataInterval))
        {
            log_e("[Firebase] FAILED - REASON: %s", fbdata.errorReason().c_str());
            return;
        }

        log_i("[Firebase] PASSED - PATH: %s, TYPE: %s", fbdata.dataType().c_str(), fbdata.dataPath().c_str());
        _sendDataInterval++;

        // Write an Float number on the database path test/float
        if (!Firebase.RTDB.setFloat(&fbdata, "test/float", 0.01 + random(0, 100)))
        {
            log_e("[Firebase] FAILED - REASON: %s", fbdata.errorReason().c_str());
            return;
        }

        log_i("[Firebase] PASSED - PATH: %s, TYPE: %s", fbdata.dataType().c_str(), fbdata.dataPath().c_str());
    }
}