import * as React from 'react';
import Container from '@mui/material/Container';
import Typography from '@mui/material/Typography';
import Box from '@mui/material/Box';
import ProTip from './components/protip';
import Copyright from './components/copyright';
import './styles/App.css'

function App() {
  const [count, setCount] = React.useState(0);
  
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
