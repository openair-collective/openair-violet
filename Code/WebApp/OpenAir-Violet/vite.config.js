import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import { resolve } from 'path'

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [react()],
  alias: {
    '@': resolve(__dirname, 'src'),
    '@components': resolve(__dirname, 'src/components'),
    '@pages': resolve(__dirname, 'src/pages'),
    '@utils': resolve(__dirname, 'src/utils'),
    '@assets': resolve(__dirname, 'src/assets'),
    '@styles': resolve(__dirname, 'src/styles'),
    '@constants': resolve(__dirname, 'src/constants'),
    '@api': resolve(__dirname, 'src/api'),
    '@router': resolve(__dirname, 'src/router'),
    '@store': resolve(__dirname, 'src/store'),
    '@actions': resolve(__dirname, 'src/actions'),
    '@models': resolve(__dirname, 'src/models'),
  },
  define: {
    'process.env': process.env
  }
})
