from pathlib import Path

from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles
from api.app.routers import heroes

app = FastAPI(
    title="The Lost Force",
    description="Front-end representation of the backend side",
    version="1.2"
)

app.include_router(heroes.router)
BASE_DIR = Path(__file__).resolve().parent

app.mount("/images", StaticFiles(directory=BASE_DIR / "images"), name="images")

@app.get("/")
def main_page():
    return "Welcome to The Lost Force"