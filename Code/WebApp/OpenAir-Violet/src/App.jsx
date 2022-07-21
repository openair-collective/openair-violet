import * as React from 'react';
import Container from '@mui/material/Container';
import Typography from '@mui/material/Typography';
import Box from '@mui/material/Box';
import ProTip from './components/protip';
import Copyright from './components/copyright';
import './styles/App.css'
import firebasedata from './utils/firebasedata'

// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
//import { auth } from "firebase/auth";
//import { database } from 'firebase/database';
//import { firestore } from "firebase/firestore";
import { getAnalytics } from "firebase/analytics";
import { getFirestore, collection, getDocs } from 'firebase/firestore/lite';
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyARBFtgr3pjHfCQX1MboS80DIut9FxvCls",
  authDomain: "openair-violet.firebaseapp.com",
  databaseURL: "https://openair-violet-default-rtdb.europe-west1.firebasedatabase.app",
  projectId: "openair-violet",
  storageBucket: "openair-violet.appspot.com",
  messagingSenderId: "428155808003",
  appId: "1:428155808003:web:30a08a4f8d24f9287da136",
  measurementId: "G-TL860G29X5"
};

// Initialize Firebase
const firebase = initializeApp(firebaseConfig);
const db = getFirestore(firebase);

const analytics = getAnalytics(firebase);

const dataFloatPath = firebasedata.data_paths.float;
const dataIntPath = firebasedata.data_paths.int;

// Variables to save database current values
var floatReading;
var intReading;

async function getData(db) {
  const dataCol = collection(db, 'test');
  const dataSnapshot = await getDocs(dataCol);
  const dataList = dataSnapshot.docs.map(doc => doc.data());
  return dataList;
}



function App() {
  const [count, setCount] = React.useState(0)
  // use effect to get data from firebase
  React.useEffect(() => {
    getData(db).then(data => {
      console.log(data);
      //floatReading = data[0][dataFloatPath];
      //intReading = data[0][dataIntPath];
    }
    );
  }, []);
  return (
    <Container maxWidth="sm">
      <Box sx={{ my: 4 }}>
        <Typography variant="h4" component="h1" gutterBottom>
          <p>Reading int: <span id="reading-int"></span></p>
          <p>Reading float: <span id="reading-float"></span></p>
        </Typography>
        <ProTip />
        <Copyright />
      </Box>
    </Container>
  )
}

export default App
