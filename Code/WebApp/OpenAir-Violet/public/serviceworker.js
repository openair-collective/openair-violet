// Generate service worker for a Progressive Web App
const CACHE_NAME = 'openair-violet-cache-v1';

const urlsToCache = [
    'index.html',
    'offline.html',
    '/assets/index.a4305b28.js',
    '/assets/index.c277f549.css',
    /* '/css/style.css',
    '/css/style-dark.css',
    '/css/style-light.css',
    '/css/style-mobile.css' */
];

const self = this;

// Install a service worker
self.addEventListener('install', (event) => {
    event.waitUntil(
        caches.open(CACHE_NAME)
            .then((cache) => {
                console.log('Opened cache');
                return cache.addAll(urlsToCache);
            })
    );
});

// Listen for requests
self.addEventListener('fetch', (event) => {
    event.respondWith(
        caches.match(event.request)
            .then(() => {
                // Cache miss - return fetch() request
                return fetch(event.request)
                    .catch(() => caches.match('offline.html'));
            }));

});

//Activate the service worker
self.addEventListener('activate', (event) => {
    const cacheWhiteList = [];
    cacheWhiteList.push(CACHE_NAME);

    event.waitUntil(
        caches.keys().then((cacheNames) => {
            return Promise.all(
                cacheNames.map((cacheName) => {
                    if (!cacheWhiteList.includes(cacheName)) {
                        return caches.delete(cacheName);
                    }
                })
            );
        })
    );

});