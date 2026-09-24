(() => {
  'use strict';
  const data = JSON.parse(document.getElementById('reference-data').textContent);
  const search = document.getElementById('search');
  const world = document.getElementById('world-filter');
  const entries = [...document.querySelectorAll('.searchable')];
  const searchableText = new Map(entries.map(el => {
    const copy = el.cloneNode(true);
    copy.querySelectorAll('.source, pre').forEach(node => node.remove());
    return [el, (copy.textContent + ' ' + el.id + ' world ' + el.dataset.world).toLowerCase().replace(/\s+/g, ' ')];
  }));
  function filter() {
    const terms = search.value.trim().toLowerCase().split(/\s+/).filter(Boolean);
    let shown = 0;
    entries.forEach(el => {
      const text = searchableText.get(el);
      const matchText = terms.every(term => text.includes(term));
      const matchWorld = world.value === 'all' || el.dataset.world === world.value || el.dataset.world === 'all';
      el.hidden = !(matchText && matchWorld);
      if (!el.hidden && !el.classList.contains('world')) shown++;
    });
    document.querySelectorAll('.world').forEach(el => {
      if ([...el.querySelectorAll('.map')].some(map => !map.hidden)) el.hidden = false;
    });
    document.getElementById('search-status').textContent = terms.length || world.value !== 'all' ? `${shown} matching catalog entries` : 'Browse the complete reference';
    document.getElementById('no-results').hidden = shown > 0;
  }
  search.addEventListener('input', filter);
  world.addEventListener('change', filter);
  document.getElementById('reset-filter').addEventListener('click', () => { search.value = ''; world.value = 'all'; filter(); });
  document.getElementById('print').addEventListener('click', () => window.print());

  const key = 'sakura-reference-card-checklist-v1';
  let checked = [];
  let storageAvailable = true;
  try { const saved = JSON.parse(localStorage.getItem(key) || '[]'); checked = Array.isArray(saved) ? saved.filter(n => Number.isInteger(n) && n >= 0 && n < 52) : []; }
  catch (_) { storageAvailable = false; }
  const boxes = [...document.querySelectorAll('[data-card]')];
  function updateChecklist() {
    checked = boxes.filter(box => box.checked).map(box => Number(box.dataset.card));
    boxes.forEach(box => box.closest('article').classList.toggle('checked', box.checked));
    try { localStorage.setItem(key, JSON.stringify(checked)); } catch (_) { storageAvailable = false; }
    document.getElementById('check-status').textContent = `${checked.length} / 52 marked${storageAvailable ? ' in this browser' : ' for this page session (storage unavailable)'}`;
  }
  boxes.forEach(box => { box.checked = checked.includes(Number(box.dataset.card)); box.addEventListener('change', updateChecklist); });
  updateChecklist();
  document.getElementById('clear-checklist').addEventListener('click', () => { boxes.forEach(box => { box.checked = false; }); updateChecklist(); });

  const alphaMasks = new Map();
  async function loadAlphaMasks(worldId) {
    if (alphaMasks.has(worldId)) return alphaMasks.get(worldId);
    const profile = data.collisionProfiles[worldId];
    const loading = (async () => {
      if (!profile.alphaAtlas) return {};
      const atlas = new Image();
      atlas.src = profile.alphaAtlas;
      await atlas.decode();
      const surface = document.createElement('canvas');
      surface.width = atlas.width; surface.height = atlas.height;
      const context = surface.getContext('2d');
      context.drawImage(atlas, 0, 0);
      const masks = {};
      Object.entries(profile.alphaRects).forEach(([token, [x, y]]) => {
        const pixels = context.getImageData(x, y, 20, 20).data;
        masks[token] = Array.from({ length: 400 }, (_, index) => pixels[index * 4 + 3] > 2.55);
      });
      return masks;
    })();
    alphaMasks.set(worldId, loading);
    return loading;
  }
  async function drawMap(id) {
    const map = data.maps[id];
    let masks;
    try { masks = await loadAlphaMasks(map.world); }
    catch (_) {
      const button = document.querySelector(`.draw-map[data-map="${id}"]`);
      button.textContent = 'Atlas could not be read. Click to retry.';
      alphaMasks.delete(map.world);
      return;
    }
    const nonSolid = new Set(data.collisionProfiles[map.world].nonSolid);
    const scale = Number(document.querySelector(`.map-scale[data-map="${id}"]`).value);
    const cell = 20 * scale;
    const canvas = document.getElementById(`canvas-${id}`);
    canvas.hidden = false;
    canvas.width = Math.ceil(map.width * cell);
    canvas.height = Math.ceil(map.height * cell);
    const ctx = canvas.getContext('2d');
    ctx.fillStyle = '#edf0e9'; ctx.fillRect(0, 0, canvas.width, canvas.height);
    for (let y = 0; y < map.height; y++) {
      for (let x = 0; x < map.width; x++) {
        const token = map.tokens[y * map.width + x];
        if (!token || nonSolid.has(token)) continue;
        ctx.fillStyle = '#385665';
        if (masks[token]) {
          for (let py = 0; py < 20; py++) {
            for (let px = 0; px < 20; px++) {
              if (masks[token][py * 20 + px]) ctx.fillRect(x * cell + px * scale, y * cell + py * scale, scale, scale);
            }
          }
        } else ctx.fillRect(x * cell, y * cell, cell, cell);
      }
    }
    const dot = (pos, color, radius) => {
      ctx.beginPath(); ctx.arc(pos[0] * scale, pos[1] * scale, radius, 0, Math.PI * 2);
      ctx.fillStyle = color; ctx.fill(); ctx.lineWidth = 1; ctx.strokeStyle = '#fff'; ctx.stroke();
    };
    map.cards.forEach(pos => dot(pos, '#e8b245', Math.max(3, 8 * scale)));
    dot(map.start, '#65b28b', Math.max(4, 10 * scale));
  }
  document.querySelectorAll('.draw-map').forEach(button => button.addEventListener('click', () => drawMap(button.dataset.map)));
  document.querySelectorAll('.map-scale').forEach(select => select.addEventListener('change', () => drawMap(select.dataset.map)));
  document.getElementById('source-select').addEventListener('change', event => {
    document.getElementById('source-view').textContent = data.scripts[event.target.value] || 'Choose a file above.';
  });
  function revealHash() {
    const id = decodeURIComponent(location.hash.slice(1));
    const target = document.getElementById(id);
    if (!target) return;
    if (target.hidden || target.closest('[hidden]')) { search.value = ''; world.value = 'all'; filter(); }
    if (target.matches('details')) target.open = true;
    let parent = target.parentElement;
    while (parent) { if (parent.matches('details')) parent.open = true; parent = parent.parentElement; }
    requestAnimationFrame(() => target.scrollIntoView({ block: 'start' }));
  }
  window.addEventListener('hashchange', revealHash);
  if (location.hash) revealHash();
  if ('IntersectionObserver' in window) {
    const observer = new IntersectionObserver(items => {
      items.forEach(item => {
        if (!item.isIntersecting) return;
        document.querySelectorAll('nav a').forEach(link => {
          const active = link.getAttribute('href') === '#' + item.target.id;
          link.classList.toggle('active', active);
          if (active) link.setAttribute('aria-current', 'location'); else link.removeAttribute('aria-current');
        });
      });
    }, { rootMargin: '-10% 0px -65% 0px' });
    document.querySelectorAll('main > section').forEach(section => observer.observe(section));
  }
})();
