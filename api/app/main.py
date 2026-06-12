from fastapi import FastAPI
from api.app.routers import heroes

app = FastAPI(
    title="The Lost Force",
    description="Front-end representation of the backend side",
    version="1.2"
)

app.include_router(heroes.router)

@app.get("/")
def main_page():
    return "Welcome to The Lost Force"