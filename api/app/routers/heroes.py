from fastapi import APIRouter, Depends, HTTPException, Request
from fastapi.templating import Jinja2Templates
from sqlalchemy import text
from sqlalchemy.orm import Session
from api.app.database import get_db

router = APIRouter(
    prefix="/heroes"
)

templates = Jinja2Templates(directory="templates")

@router.get("/")
def get_all_heroes(request: Request, db: Session = Depends(get_db)):
    heroes = db.execute(
        text("SELECT * FROM heroes;")
    ).mappings().all()

    return templates.TemplateResponse(
        request=request,
        name="heroes.html",
        context={"heroes": heroes}
    )

@router.get("/{id}")
def get_one_hero(id: int, db: Session = Depends(get_db)):
    result = db.execute(
        text("SELECT * FROM heroes WHERE id = :id;"),
        {"id": id}
    ).mappings().first()

    if not result:
        raise HTTPException(status_code=404, detail="Hero not found")

    return {
        "hero": dict(result)
    }

@router.delete("/{id}")
def delete_one_hero(id: int, db: Session = Depends(get_db)):
    result = db.execute(
        text("DELETE FROM heroes WHERE id == :id;"),
        {"id": id}
    ).mappings().first()

    if not result:
        raise HTTPException(status_code=404, detail="Hero not found")

    return {
        "hero": dict(result)
    }


