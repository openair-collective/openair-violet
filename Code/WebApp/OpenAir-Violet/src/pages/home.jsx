import * as React from 'react';

//* 
//* * MUI Theme Provider
//*
import { Button, Box, Typography, Container, Paper, Grid, Switch } from '@mui/material';
import CssBaseline from '@mui/material/CssBaseline';
import { ThemeProvider } from '@mui/material/styles';
import { makeStyles } from '@mui/styles';
import { createTheme } from '@mui/material/styles';
import { red } from '@mui/material/colors';

//* 
//* * Components
//*
import ProTip from '../components/protip';
import Copyright from '../components/copyright';
import '../styles/App.css'

//* 
//* * Firebase
//*
//Firebase imports
import { db } from '../components/firebase';
import { uid } from 'uid';
import { set, ref, onValue, remove, update } from 'firebase/database';

const uiDefaults = {
  APPBAR_HEIGHT: 1000,
}
const useStyles = makeStyles(theme => ({
  root: {
    height: "100vh"
  },
  grid: {
    height: "100vh",
    width: '100vw',
    spacing: 0,
    justify: 'space-around'
  },
  middleGrid: {
    height: `calc(100vh - ${uiDefaults.APPBAR_HEIGHT})`,
    spacing: 0,
    direction: 'column'
  },
  paperLeft: {
    height: "90%"
  },
  paperTop: {},
  paperMain: {
    height: "90%"
  },
paperRight: { height : "100%" },
  paperBottom: { height: "20%" },
  paper: {
    padding: theme.spacing(1),
    textAlign: "center",
    color: theme.palette.text.primary,
    background: theme.palette.grey,
    margin: theme.spacing(1),
    borderRadius: theme.shape.borderRadius,
    boxShadow: theme.shadows[2],
    '&:hover': {
      backgroundColor: theme.palette.background.default,
      boxShadow: theme.shadows[3],
    }
  }
}));

const FullWidthGrid = ({ toggleDark, settoggleDark }) => {
  const [count, setCount] = React.useState(0);
  const [todo, setToDo] = React.useState("");
  const [todos, setToDos] = React.useState([]);
  const [isEdit, setIsEdit] = React.useState(false);
  const [tempUUID, setTempUUID] = React.useState("");

  const handleModeChange = () => {
    settoggleDark(!toggleDark)
  };

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
  const classes = useStyles();
  return (
    <Container maxWidth="lg" className={classes.root}>
      <Grid container className={classes.grid}>
        <Grid item xs={12}>
          <Paper className={`${classes.paperTop} ${classes.paper}`}>
            <Box display="flex" justifyContent="center">
              <Typography variant="body2" component="p" color="text.secondary" align="center">
                {toggleDark ? "Dark" : "Light"}
                <Switch
                  checked={toggleDark}
                  onChange={handleModeChange}
                  name="toggleDark"
                  color="default"
                />
              </Typography>
            </Box>
          </Paper>
        </Grid>
        <Grid container className={classes.middleGrid}>
          <Grid item container xs={12} spacing={1}>
            <Grid item xs={2}>
              <Paper className={`${classes.paperLeft} ${classes.paper}`}>
                xs=12 sm=6
              </Paper>
            </Grid>
            <Grid item xs={10}>
              <Paper className={`${classes.paperMain} ${classes.paper}`}>
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
                    <Button variant="contained" color="primary" onClick={() => { handleSubmitChange(); setIsEdit(false); setToDo("") }}>
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
                </Box>
              </Paper>
            </Grid>
          </Grid>
        </Grid>
        <Grid item xs={12}>
          <Copyright />
        </Grid>
      </Grid>
    </Container>
  );
}



function HomePage() {
  const [toggleDark, settoggleDark] = React.useState(false);
  // Create a theme instance.
  const theme = createTheme({
    palette: {
      primary: {
        main: '#556cd6',
      },
      secondary: {
        main: '#19857b',
      },
      error: {
        main: red.A400,
      },
      mode: toggleDark ? 'dark' : 'light',
    },
    components: {
      MuiTextField: {
        defaultProps: {
          variant: 'outlined',
        },
      },
    },
  });
  return (
    <>
      <ThemeProvider theme={theme}>
        {/* CssBaseline kickstart an elegant, consistent, and simple baseline to build upon. */}
        <CssBaseline enableColorScheme />
        <FullWidthGrid toggleDark={toggleDark} settoggleDark={settoggleDark} />
      </ThemeProvider>
    </>
  )
}

export default HomePage
