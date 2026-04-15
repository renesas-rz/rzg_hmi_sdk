import './App.css';
import { HashRouter, Routes, Route } from 'react-router-dom';

import { PlasmicHomepage } from './components/plasmic/Plasmic_sample_app/PlasmicHomepage';
import { PlasmicJpg } from './components/plasmic/Plasmic_sample_app/PlasmicJpg';
import { PlasmicGif } from './components/plasmic/Plasmic_sample_app/PlasmicGif';

import { StyleTokensProvider } from './components/plasmic/Plasmic_sample_app/PlasmicStyleTokensProvider';
import GlobalContextsProvider from './components/plasmic/Plasmic_sample_app/PlasmicGlobalContextsProvider';

function App() {
  return (
    <StyleTokensProvider>
      <GlobalContextsProvider>
        <HashRouter>
          <Routes>
            <Route path="/" element={<PlasmicHomepage />} />
            <Route path="/jpg" element={<PlasmicJpg />} />
            <Route path="/gif" element={<PlasmicGif />} />
          </Routes>
        </HashRouter>
      </GlobalContextsProvider>
    </StyleTokensProvider>
  );
}

export default App;