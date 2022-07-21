import * as React from 'react';
import { Button, Box, Typography, Container } from '@mui/material';
import ProTip from '../components/protip';
import Copyright from '../components/copyright';
import '../styles/App.css'

//Firebase imports
import { db } from '../components/firebase';
import { uid } from 'uid';
import { set, ref, onValue, remove, update } from 'firebase/database';

function HomePage() {
  const [count, setCount] = React.useState(0);
  const [todo, setToDo] = React.useState("");
  const [todos, setToDos] = React.useState([]);
  const [isEdit, setIsEdit] = React.useState(false);
  const [tempUUID, setTempUUID] = React.useState("");

  const handleToDoChange = (event) => {
    setToDo(event.target.value);
  }

  const handleCountChange = (event) => {
    setCount(count + 1);
  }

  //write
  const writeData = () => {
    const uuid = uid();
    set(ref(db, `/${uuid}`), {
      todo: todo,
      uuid: uuid,
      count: count
    });
    setToDo("");
  }

  //read
  React.useEffect(() => {
    onValue(ref(db), (snapshot) => {
      setToDos([]);
      //console.log(snapshot.val());
      const data = snapshot.val();
      if (data !== null) {
        Object.values(data).map((todo) => {
          setToDos(oldArray => [...oldArray, todo]);
        });
      }
    }, (error) => {
      console.log(error);
    }
    );
  }, []);

  //update
  const handleUpdateData = (todo) => {
    setIsEdit(true);
    setTempUUID(todo.uuid);
    setToDo(todo.todo);
  }

  const handleSubmitChange = () => {
    update(ref(db, `/${tempUUID}`), {
      todo,
      uuid: tempUUID,
      count: count
    });
    setToDo("");
    setIsEdit(false);
  }
  //delete
  const handleDelete = (todo) => {
    remove(ref(db, `/${todo.uuid}`));
  }

  return (
    <Container maxWidth="sm">
      <Box sx={{ my: 4 }}>
        <Typography variant="h4" component="h1" gutterBottom>
          <p>Reading int: <span id="reading-int"></span></p>
          <p>Reading float: <span id="reading-float"></span></p>
        </Typography>
        <Button variant="contained" color="primary" onClick={handleCountChange}>
          Count
        </Button>
        <input type="text" value={todo} onChange={handleToDoChange} />
        {isEdit ? (
          <Button variant="contained" color="primary" onClick={() => {handleSubmitChange(); setIsEdit(false); setToDo("")}}>
            Submit Changes
          </Button>
        ) : (
          <Button variant="contained" color="primary" onClick={writeData}>submit</Button>
        )}
        {todos.map((todo) => (
          <div key={todo.uuid}>
            <Typography variant="h4" component="h1" gutterBottom>
              {todo.todo}
            </Typography>
            <p>{todo.count}</p>
            <Button variant="contained" color="primary" onClick={() => handleUpdateData(todo)}>
              update
            </Button>
            <Button variant="contained" color="primary" onClick={() => handleDelete(todo)}>
              delete
            </Button>
          </div>
        ))}
        <ProTip />
        <Copyright />
      </Box>
    </Container>
  )
}

export default HomePage
