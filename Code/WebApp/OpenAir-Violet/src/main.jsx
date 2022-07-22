import * as React from 'react';
import { createRoot } from 'react-dom/client';
import HomePage from './pages/home';



const rootElement = document.getElementById('root');
const root = createRoot(rootElement);

root.render(
  <React.StrictMode>
    <HomePage />
  </React.StrictMode>,
);